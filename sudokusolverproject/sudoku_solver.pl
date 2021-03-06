in_str(Str,L):-
    string_to_list(Str,S),
    sudoku_list(S,L).
sudoku_list([],[]).
sudoku_list([X|XS],L2) :-
    (   between(48,57,X) ->
    S is X - 48;
    between(65,70,X) ->
    S is X -55;
    S = _),
    append([S],L1,L2),
    sudoku_list(XS,L1).
    
replace(_, _, [], []).
replace(O, R, [O|T], [R|T2]) :- replace(O, R, T, T2).
replace(O, R, [H|T], [H|T2]) :- H \= O, replace(O, R, T, T2).

:- use_module(library(clpfd)).

sudoku([A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14,A15,A16,
       B1,B2,B3,B4,B5,B6,B7,B8,B9,B10,B11,B12,B13,B14,B15,B16,
       C1,C2,C3,C4,C5,C6,C7,C8,C9,C10,C11,C12,C13,C14,C15,C16, 
       D1,D2,D3,D4,D5,D6,D7,D8,D9,D10,D11,D12,D13,D14,D15,D16,        
       E1,E2,E3,E4,E5,E6,E7,E8,E9,E10,E11,E12,E13,E14,E15,E16,
       F1,F2,F3,F4,F5,F6,F7,F8,F9,F10,F11,F12,F13,F14,F15,F16,
       G1,G2,G3,G4,G5,G6,G7,G8,G9,G10,G11,G12,G13,G14,G15,G16,
       H1,H2,H3,H4,H5,H6,H7,H8,H9,H10,H11,H12,H13,H14,H15,H16,
       I1,I2,I3,I4,I5,I6,I7,I8,I9,I10,I11,I12,I13,I14,I15,I16,
       J1,J2,J3,J4,J5,J6,J7,J8,J9,J10,J11,J12,J13,J14,J15,J16,
       K1,K2,K3,K4,K5,K6,K7,K8,K9,K10,K11,K12,K13,K14,K15,K16,
       L1,L2,L3,L4,L5,L6,L7,L8,L9,L10,L11,L12,L13,L14,L15,L16,
       M1,M2,M3,M4,M5,M6,M7,M8,M9,M10,M11,M12,M13,M14,M15,M16,
       N1,N2,N3,N4,N5,N6,N7,N8,N9,N10,N11,N12,N13,N14,N15,N16,
       O1,O2,O3,O4,O5,O6,O7,O8,O9,O10,O11,O12,O13,O14,O15,O16,
       P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14,P15,P16],Y) :-
 
       valid([A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14,A15,A16]),
       valid([B1,B2,B3,B4,B5,B6,B7,B8,B9,B10,B11,B12,B13,B14,B15,B16]),
       valid([C1,C2,C3,C4,C5,C6,C7,C8,C9,C10,C11,C12,C13,C14,C15,C16]),
       valid([D1,D2,D3,D4,D5,D6,D7,D8,D9,D10,D11,D12,D13,D14,D15,D16]),
       
       valid([E1,E2,E3,E4,E5,E6,E7,E8,E9,E10,E11,E12,E13,E14,E15,E16]),
       valid([F1,F2,F3,F4,F5,F6,F7,F8,F9,F10,F11,F12,F13,F14,F15,F16]),
       valid([G1,G2,G3,G4,G5,G6,G7,G8,G9,G10,G11,G12,G13,G14,G15,G16]),
       valid([H1,H2,H3,H4,H5,H6,H7,H8,H9,H10,H11,H12,H13,H14,H15,H16]),
       
       valid([I1,I2,I3,I4,I5,I6,I7,I8,I9,I10,I11,I12,I13,I14,I15,I16]),
       valid([J1,J2,J3,J4,J5,J6,J7,J8,J9,J10,J11,J12,J13,J14,J15,J16]),
       valid([K1,K2,K3,K4,K5,K6,K7,K8,K9,K10,K11,K12,K13,K14,K15,K16]),
       valid([L1,L2,L3,L4,L5,L6,L7,L8,L9,L10,L11,L12,L13,L14,L15,L16]),
      
       valid([M1,M2,M3,M4,M5,M6,M7,M8,M9,M10,M11,M12,M13,M14,M15,M16]),
       valid([N1,N2,N3,N4,N5,N6,N7,N8,N9,N10,N11,N12,N13,N14,N15,N16]),
       valid([O1,O2,O3,O4,O5,O6,O7,O8,O9,O10,O11,O12,O13,O14,O15,O16]),
       valid([P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14,P15,P16]),


       valid([A1,B1,C1,D1,E1,F1,G1,H1,I1,J1,K1,L1,M1,N1,O1,P1]),
       valid([A2,B2,C2,D2,E2,F2,G2,H2,I2,J2,K2,L2,M2,N2,O2,P2]),
       valid([A3,B3,C3,D3,E3,F3,G3,H3,I3,J3,K3,L3,M3,N3,O3,P3]),
       valid([A4,B4,C4,D4,E4,F4,G4,H4,I4,J4,K4,L4,M4,N4,O4,P4]),
       
       valid([A5,B5,C5,D5,E5,F5,G5,H5,I5,J5,K5,L5,M5,N5,O5,P5]),
       valid([A6,B6,C6,D6,E6,F6,G6,H6,I6,J6,K6,L6,M6,N6,O6,P6]),
       valid([A7,B7,C7,D7,E7,F7,G7,H7,I7,J7,K7,L7,M7,N7,O7,P7]),
       valid([A8,B8,C8,D8,E8,F8,G8,H8,I8,J8,K8,L8,M8,N8,O8,P8]),
       
       valid([A9,B9,C9,D9,E9,F9,G9,H9,I9,J9,K9,L9,M9,N9,O9,P9]),
       valid([A10,B10,C10,D10,E10,F10,G10,H10,I10,J10,K10,L10,M10,N10,O10,P10]),
       valid([A11,B11,C11,D11,E11,F11,G11,H11,I11,J11,K11,L11,M11,N11,O11,P11]),
       valid([A12,B12,C12,D12,E12,F12,G12,H12,I12,J12,K12,L12,M12,N12,O12,P12]),
       
       valid([A13,B13,C13,D13,E13,F13,G13,H13,I13,J13,K13,L13,M13,N13,O13,P13]),
       valid([A14,B14,C14,D14,E14,F14,G14,H14,I14,J14,K14,L14,M14,N14,O14,P14]),
       valid([A15,B15,C15,D15,E15,F15,G15,H15,I15,J15,K15,L15,M15,N15,O15,P15]),
       valid([A16,B16,C16,D16,E16,F16,G16,H16,I16,J16,K16,L16,M16,N16,O16,P16]),
 
       valid([A1,A2,A3,A4,B1,B2,B3,B4,C1,C2,C3,C4,D1,D2,D3,D4]),
       valid([A5,A6,A7,A8,B5,B6,B7,B8,C5,C6,C7,C8,D5,D6,D7,D8]),
       valid([A9,A10,A11,A12,B9,B10,B11,B12,C9,C10,C11,C12,D9,D10,D11,D12]),
       valid([A13,A14,A15,A16,B13,B14,B15,B16,C13,C14,C15,C16,D13,D14,D15,D16]),
       
       valid([E1,E2,E3,E4,F1,F2,F3,F4,G1,G2,G3,G4,H1,H2,H3,H4]),
       valid([E5,E6,E7,E8,F5,F6,F7,F8,G5,G6,G7,G8,H5,H6,H7,H8]),
       valid([E9,E10,E11,E12,F9,F10,F11,F12,G9,G10,G11,G12,H9,H10,H11,H12]),
       valid([E13,E14,E15,E16,F13,F14,F15,F16,G13,G14,G15,G16,H13,H14,H15,H16]),
       
       valid([I1,I2,I3,I4,J1,J2,J3,J4,K1,K2,K3,K4,L1,L2,L3,L4]),
       valid([I5,I6,I7,I8,J5,J6,J7,J8,K5,K6,K7,K8,L5,L6,L7,L8]),
       valid([I9,I10,I11,I12,J9,J10,J11,J12,K9,K10,K11,K12,L9,L10,L11,L12]),
       valid([I13,I14,I15,I16,J13,J14,J15,J16,K13,K14,K15,K16,L13,L14,L15,L16]),
       
       valid([M1,M2,M3,M4,N1,N2,N3,N4,O1,O2,O3,O4,P1,P2,P3,P4]),
       valid([M5,M6,M7,M8,N5,N6,N7,N8,O5,O6,O7,O8,P5,P6,P7,P8]),
       valid([M9,M10,M11,M12,N9,N10,N11,N12,O9,O10,O11,O12,P9,P10,P11,P12]),
       valid([M13,M14,M15,M16,N13,N14,N15,N16,O13,O14,O15,O16,P13,P14,P15,P16]),
       
       
       labeling([ff],[A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14,A15,A16,
                    B1,B2,B3,B4,B5,B6,B7,B8,B9,B10,B11,B12,B13,B14,B15,B16,
                    C1,C2,C3,C4,C5,C6,C7,C8,C9,C10,C11,C12,C13,C14,C15,C16,
                    D1,D2,D3,D4,D5,D6,D7,D8,D9,D10,D11,D12,D13,D14,D15,D16,
                    E1,E2,E3,E4,E5,E6,E7,E8,E9,E10,E11,E12,E13,E14,E15,E16,
                    F1,F2,F3,F4,F5,F6,F7,F8,F9,F10,F11,F12,F13,F14,F15,F16,
                    G1,G2,G3,G4,G5,G6,G7,G8,G9,G10,G11,G12,G13,G14,G15,G16,
                    H1,H2,H3,H4,H5,H6,H7,H8,H9,H10,H11,H12,H13,H14,H15,H16,
                    I1,I2,I3,I4,I5,I6,I7,I8,I9,I10,I11,I12,I13,I14,I15,I16,
                    J1,J2,J3,J4,J5,J6,J7,J8,J9,J10,J11,J12,J13,J14,J15,J16,
                    K1,K2,K3,K4,K5,K6,K7,K8,K9,K10,K11,K12,K13,K14,K15,K16,
                    L1,L2,L3,L4,L5,L6,L7,L8,L9,L10,L11,L12,L13,L14,L15,L16,
                    M1,M2,M3,M4,M5,M6,M7,M8,M9,M10,M11,M12,M13,M14,M15,M16,
                    N1,N2,N3,N4,N5,N6,N7,N8,N9,N10,N11,N12,N13,N14,N15,N16,
                    O1,O2,O3,O4,O5,O6,O7,O8,O9,O10,O11,O12,O13,O14,O15,O16,
                    P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14,P15,P16]),
 
       Y = [A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14,A15,A16,B1,B2,B3,B4,B5,B6,B7,B8,B9,B10,B11,B12,B13,B14,B15,B15,B16,C1,C2,C3,C4,C5,C6,C7,C8,C9,C10,C11,C12,C13,C14,C15,C16,D1,D2,D3,D4,D5,D6,D7,D8,D9,D10,D11,D12,D13,D14,D15,D16,E1,E2,E3,E4,E5,E6,E7,E8,E9,E10,E11,E12,E13,E14,E15,E16,F1,F2,F3,F4,F5,F6,F7,F8,F9,F10,F11,F12,F13,F14,F15,F16,G1,G2,G3,G4,G5,G6,G7,G8,G9,G10,G11,G12,G13,G14,G15,G16,H1,H2,H3,H4,H5,H6,H7,H8,H9,H10,H11,H12,H13,H14,H15,H16,I1,I2,I3,I4,I5,I6,I7,I8,I9,I10,I11,I12,I13,I14,I15,I16,J1,J2,J3,J4,J5,J6,J7,J8,J9,J10,J11,J12,J13,J14,J15,J16,K1,K2,K3,K4,K5,K6,K7,K8,K9,K10,K11,K12,K13,K14,K15,K16,L1,L2,L3,L4,L5,L6,L7,L8,L9,L10,L11,L12,L13,L14,L15,L16,M1,M2,M3,M4,M5,M6,M7,M8,M9,M10,M11,M12,M13,M14,M15,M16,N1,N2,N3,N4,N5,N6,N7,N8,N9,N10,N11,N12,N13,N14,N15,N16,O1,O2,O3,O4,O5,O6,O7,O8,O9,O10,O11,O12,O13,O14,O15,O16,P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14,P15,P16].
	
 
valid(L) :-
    length(L,16),
    L ins 0..15,
    all_different(L).
 


solve_prolog(X,Y) :-
    in_str(X,L),
    sudoku(L,Out),
    replace(10,a,Out,A),
    replace(11,b,A,B),
    replace(12,c,B,C),
    replace(13,d,C,D),
    replace(14,e,D,E),
    replace(15,f,E,W),
    concat_atom(W,Y),
    print(Y).
