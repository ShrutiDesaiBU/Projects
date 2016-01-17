import sys
## Throughout this program we have:
##   r is a row,    e.g. 'A'
##   c is a column, e.g. '3'
##   s is a square, e.g. 'A3'
##   d is a digit,  e.g. '9'
##   u is a unit,   e.g. ['A1','B1','C1','D1','E1','F1','G1','H1','I1','J1','K1','L1','M1','N1','O1','P1']
##   grid is a grid,e.g. 256 non-blank chars, e.g. starting with '.18...7...
##   values is a dict of possible values, e.g. {'A1':'12349', 'A2':'8', ...}

def cross(A, B):
    "Cross product of elements in A and elements in B."
    return [a+b for a in A for b in B]

digits   = '0123456789ABCDEF'
rows     = 'ABCDEFGHIJKLMNOP'
cols     = digits
squares  = cross(rows, cols)
unitlist = ([cross(rows, c) for c in cols] +
            [cross(r, cols) for r in rows] +
            [cross(rs, cs) for rs in ('ABCD','EFGH','IJKL','MNOP') for cs in ('0123','4567','89AB','CDEF')])
units = dict((s, [u for u in unitlist if s in u])
             for s in squares)
peers = dict((s, set(sum(units[s],[]))-set([s]))
             for s in squares)



################ Parse a Grid ################

def parse_grid(grid):
    """Convert grid to a dict of possible values, {square: digits}, or
    return False if a contradiction is detected."""
    ## To start, every square can be any digit; then assign values from the grid.
    values = dict((s, digits) for s in squares)
    for s,d in grid_values(grid).items():
        if d in digits and not assign(values, s, d):
            return False ## (Fail if we can't assign d to square s.)
    return values

def grid_values(grid):
    "Convert grid into a dict of {square: char} with '0' or '.' for empties."
    chars = [c for c in grid if c in digits or c in '0.']
    assert len(chars) == 256
    return dict(zip(squares, chars))

################ Constraint Propagation ################

def assign(values, s, d):
    """Eliminate all the other values (except d) from values[s] and propagate.
    Return values, except return False if a contradiction is detected."""
    other_values = values[s].replace(d, '')
    if all(eliminate(values, s, d2) for d2 in other_values):
        return values
    else:
        return False

def eliminate(values, s, d):
    """Eliminate d from values[s]; propagate when values or places <= 2.
    Return values, except return False if a contradiction is detected."""
    if d not in values[s]:
        return values ## Already eliminated
    values[s] = values[s].replace(d,'')
    ## (1) If a square s is reduced to one value d2, then eliminate d2 from the peers.
    if len(values[s]) == 0:
        return False ## Contradiction: removed last value
    elif len(values[s]) == 1:
        d2 = values[s]
        if not all(eliminate(values, s2, d2) for s2 in peers[s]):
            return False
    ## (2) If a unit u is reduced to only one place for a value d, then put it there.
    for u in units[s]:
        dplaces = [s for s in u if d in values[s]]
        if len(dplaces) == 0:
            return False ## Contradiction: no place for this value
        elif len(dplaces) == 1:
            # d can only be in one place in unit; assign it there
            if not assign(values, dplaces[0], d):
                return False
    return values

################ Display as 2-D grid ################

def display(values):
    "Display these values as a 2-D grid."
    width = 1+max(len(values[s]) for s in squares)
    line = '+'.join(['-'*(width*4)]*4)
    for r in rows:
        print (''.join(values[r+c].center(width)+('|' if c in '37B' else '')
                      for c in cols))
        if r in 'DHL': print (line)
    print

################### Search ############################

def solve(grid): return search(parse_grid(grid))

def search(values):
    "Using depth-first search and propagation, try all possible values."
    if values is False:
        return False ## Failed earlier
    if all(len(values[s]) == 1 for s in squares):
        return values ## Solved!
    ## Chose the unfilled square s with the fewest possibilities
    n,s = min((len(values[s]), s) for s in squares if len(values[s]) > 1)
    return some(search(assign(values.copy(), s, d))
                for d in values[s])

################ Utilities ################

def some(seq):
    "Return some element of seq that is true."
    for e in seq:
        if e: return e
    return False


def shuffled(seq):
    "Return a randomly shuffled copy of the input sequence."
    seq = list(seq)
    random.shuffle(seq)
    return seq

################ System test ################

import time, random, collections

def solved(values):
    "A puzzle is solved if each unit is a permutation of the digits 1 to 9."
    def unitsolved(unit): return set(values[s] for s in unit) == set(digits)
    return values is not False and all(unitsolved(unit) for unit in unitlist)


gridsEasy = '.......C.D............A0....E1..ADB.1...2..5.9.3C851.4...E0...F7.0..5.2..49CF..8.5.AC..DF3..0...17....8.....C..D...EA794.....2..7........9..5.D.F......5...D.B.A.10.......F73.6......6..382..E1..B....C..75.D894..C8B......A..5..E.D.A53C....7.F...7F9..01.8.C3.' 
gridsInter ='B............A.3.6..8A.......D.5F..D........BE....E.D...7035..F.....7....2.......F..B.E.9..C5.A.4...6...E8....0F..86.39..DF.C7.E...B..8D..A3.9.....4A...F.E7...0...9.5F....8..C.6A.C.B.4D....3.7.5..C.4..B.......0...E3..C8D...4D....F2.....7B.9..4E.7B1...9.56.'
gridsHard = '2..........6.....E0.1.F...B8.A..A.7B.D2......3E...3897..C.D...2BF26..9..5.3.........8C.A.E......4..EF.1...A7...3..9.3.4..021.8.....4...5F3..8....5..04.FD1E.9B...3F.A6....5.04..9...D.3.4......6..E.........1.FA...A..0......2.90.....B4..1C67....B.7E5...8.....'

if __name__ == '__main__':
    
    #gridToSolve=raw_input('Enter String')
    start = time.clock()
    gridToSolve=sys.argv[1];
    values2 = solve(gridToSolve)
    t=time.clock() - start
    #display(values2)
    #print 'Solved in ' + '(%.2f seconds)\n' % t
    
    if solved(values2):
    	od = collections.OrderedDict(sorted(values2.items()))
    	return_string=''.join(od.values())
    	print return_string
