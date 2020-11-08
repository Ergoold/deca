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
