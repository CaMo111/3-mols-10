import sys
import ast 
BITS = ('00', '10', '01', '11')
def main():
    glob= sys.argv[1]
    pv= sys.argv[2]
    
    sep = glob.split('X')[1:]
    sep_ = [f"X{item}" for item in sep]

    pv = list(ast.literal_eval(pv))
    chunks = [tuple(pv[i:i+4]) for i in range(0, 20, 4)]


    i=0 # can be used as offset in grabbing X strings 
    
    #parse and get all point types that have the bits specified
    ret=''
    for pc_idx, tupl in enumerate(chunks):
        for idx,r1r2val in enumerate(tupl):
            res=[]
            bit = BITS[idx]
            # iterate through all 256 points and append matching with offset to output 
            nl = []
            for point in sep_:
                offset=1+2*pc_idx
                if point[offset:offset+2]==bit:
                    nl.append(point)
                    
            nl_ = f"[{','.join(nl)}]"
            ret+=f'sumgeq({nl_},{r1r2val*10})\n'
            ret+=f'sumleq({nl_},{r1r2val*10})\n'
    
    print(ret)
    return ret         

if __name__ == "__main__":
    main()