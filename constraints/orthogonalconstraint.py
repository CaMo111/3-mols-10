import sys
import ast
from itertools import combinations, product


BITS = ('00', '10', '01', '11')

def main():
    glob= sys.argv[1]
    pv= sys.argv[2]
    
    sep = glob.split('X')[1:]
    sep_ = [f"X{item}" for item in sep]

    pv = list(ast.literal_eval(pv))
    chunks = [tuple(pv[i:i+4]) for i in range(0, 20, 4)]

    # different flow of logic for our 160 parallel classes.
    fivechoose2 = []
    fivechoose2.extend(combinations(range(5), 2))   
    
    #represents the orthogonality between our various parallel classes
    sixteen = list(product(range(4), repeat=2))

    i=0 
    j=0
    ret=''
    for combo in fivechoose2:
        pi1=chunks[combo[0]]
        pi2=chunks[combo[1]]

        for pairs in sixteen:
            nl=[]
            
            i=pairs[0]  #offset of first pair bits
            j=pairs[1]  #offset of second pair bits
            bitsI = BITS[i]
            bitsJ = BITS[j]

            for point in sep_:
                offseti=1+2*combo[0]
                offsetj=1+2*combo[1]
                if point[offseti:offseti+2]==bitsI and point[offsetj:offsetj+2]==bitsJ:
                    nl.append(point)

            res = pi1[i] * pi2[j] 

            nl_ = f"[{','.join(nl)}]"
            ret+=f'sumgeq({nl_},{res})\n'
            ret+=f'sumleq({nl_},{res})\n'
    
    print(ret)
    return ret       

if __name__ == "__main__":
    main()