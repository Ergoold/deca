#! /usr/bin/bash

function testcase {
	res=$(./deca "$2")
	if [ "$res" = "= $3" ]; then
		echo -e "test '$1':\tsuccess"
	else
		echo -e "test '$1':\tfailure"
		echo -e "\t$2"
		echo -e "\tgot\t'$res'"
		echo -e "\twanted\t'= $3'"
	fi
}

testcase basic '2 + 2' 4
testcase pemdas '1 + 2 * 2 ^ 3 + 1' 18
testcase not9 '1 + 1 * 2 * 3' 7
testcase unary+ '+7' 7
testcase times- '2 * -3 * 4' -24
testcase parens '(1 + 1) * 2' 4
testcase abs '|-7| + |7|' 14
testcase fabs '|-1.7|' 1.7
testcase float '0.3 + 0.2' 0.5
testcase minprec '0.5 + 0.5' 1
testcase dot7 '.7' 0.7
testcase 7dot '7.' 7
testcase mono '-4*3^2' -36
testcase sqroot '2v4' 2
testcase cbroot '3v8' 2
testcase root2 '2v2' 1.41421
testcase sqrt 'v16' 4
testcase phi '(1 + v5) / 2' 1.61803
testcase phi-phi 'phi - ((1 + v5) / 2)' 0
testcase 2pi '2 * pi' 6.28319
testcase minus1 '-1' -1
testcase sin1 'sin 1' 0.841471
testcase cos1p1 'cos 1 + 1' 1.5403
testcase tan-1o5 'tan (1 / 5)' 0.20271
testcase arcsin 'arcsin -1/2' -0.523599
testcase arccos 'arccos 1/2' 1.0472
testcase arctan 'arctan v2' 0.955317
testcase sinh 'sinh 3' 10.0179
testcase cosh 'cosh -2' 3.7622
testcase tanh 'tanh 1.5' 0.905148
testcase arsinh 'arsinh 10.0179' 3
testcase arcosh 'arcosh 3.7622' 2
testcase artanh 'artanh 0.905148' 1.5
testcase ln 'ln e' 1
