
# 3-MOLS-10

You may need to recompile Minion depending on what OS/env you are using. Navigate to ~/minion/README for instructions on how to compile.

## SECTION 2

`python implementation.py` 

**outputs 139 equivalence classes to classes.txt**

## SECTION 3 + SECTION 4




`source opt_env/bin/activate` \
`bash (findsinglesol.sh || findallsols_noprintsols.sh) (equivalence class index)`

**in both section 3 and section 4, a test run of equivalence class 9 (lowest enumerated) exists for reference.**

## SECTION 5

`bash compile.sh` \
`bash ./(1 || 2 || 3 || 4) eq13_1527.txt` 

If you wish to run a different $\lambda$, utilise `parseOutput.py`. Run section3 with the `-noprintsols` argument removed. Then, move the output.txt to '~/section5/output.txt' . It will subsequently produce `./stdinpt.txt`, a length 1000 binary string representing the concatenation of all points. 

