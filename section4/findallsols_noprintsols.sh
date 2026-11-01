#!/bin/bash
### PURPOSE OF THIS SCRIPT IS TO TAKE 1/139 EQ CLASSES AND CONSTRUCT the minion script which will then be used to find solutions.
### all i remember so far is like u have to correspond the value of the ith index with 10* what it is, and have the points in there or some shit 
### 2^8 different point vectors, its actually 2^10, since we have a binary string of length 10 but 2 of them will be consequently inferred or something.

#TAKE INPUT 
echo "ENTER EQUIV CLASS:"
OUT_DIR="."

LINENUM=$1
EQ=$(sed -n "${LINENUM}p" "$OUT_DIR/stripped.txt")
PV=$EQ
echo "EQUIV CLASS=: $EQ"

rm $OUT_DIR/$LINENUM/output.txt
rm $OUT_DIR/$LINENUM/consistent.min

mkdir -p $OUT_DIR/$LINENUM/
numbers=( $(echo "$EQ" | tr -d '(),') )
echo "PV: ${numbers[@]}"

echo "MINION 3" >> $OUT_DIR/$LINENUM/consistent.min
echo "**VARIABLES**" >> $OUT_DIR/$LINENUM/consistent.min

# CONSTRUCT ALL 2^8 VARIABLES = 256 POINT TYPES ~=
# a safe upper bound is 100. However, we also know another safe max upper bound we can use to cut search space is 10* max in our point vector. 
UB=$(printf '%s\n' "${numbers[@]}" | awk '{if(NR==1 || $1>max) max=$1} END {print max}')
UB_=$((UB * 10)) 

globalparam=""
for ((i=0; i<256; i++)); do
    var=$(printf "%08d\n" "$(echo "obase=2; $i" | bc)") # enumerate all 2^8=256 pv's
    #5th parallel class bits are inferred by a XOR sum of r1 and r2 bits from previous classes!  
    p5_1=$(( ${var:0:1} ^ ${var:2:1} ^ ${var:4:1} ^ ${var:6:1} ))
    p5_2=$(( ${var:1:1} ^ ${var:3:1} ^ ${var:5:1} ^ ${var:7:1} ))
    var="${var}${p5_1}${p5_2}"
    globalparam="${globalparam}X${var}"
    echo "BOUND X$var {0..$UB_}" >> $OUT_DIR/$LINENUM/consistent.min
done

# CONSTRAINTS:

echo "**CONSTRAINTS**" >> $OUT_DIR/$LINENUM/consistent.min

# global constraint, points must total to 100
python3 $PWD/../constraints/globalconstraint.py $globalparam >> $OUT_DIR/$LINENUM/consistent.min

# line constraints, match and filter bits to r1r2val*10 
python3 $PWD/../constraints/lineconstraint.py $globalparam "$PV" >> $OUT_DIR/$LINENUM/consistent.min

# orthogonal constraints, there are 160 of these. Choose 2 parallel classes, for each 16 point type combination get all points = to both and they sum to precisley the values multiplied 
python3 $PWD/../constraints/orthogonalconstraint.py $globalparam "$PV" >> $OUT_DIR/$LINENUM/consistent.min

echo "**EOF**" >> $OUT_DIR/$LINENUM/consistent.min

$PWD/../constraints/upperbound.sh $OUT_DIR/$LINENUM/consistent.min

source $PWD/opt_env/bin/activate
python3 $PWD/../constraints/pulp-bound.py $OUT_DIR/$LINENUM/consistent.min $OUT_DIR/$LINENUM/consistent.min

$PWD/../minion/bin/minion -preprocess GAC -varorder domoverwdeg -findallsols -noprintsols $OUT_DIR/$LINENUM/consistent.min >> $OUT_DIR/$LINENUM/output.txt

python3 $PWD/../constraints/extractor.py "$EQ" >> $OUT_DIR/$LINENUM/output.txt
