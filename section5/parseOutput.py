import sys
import subprocess

def main():
    eq_case = sys.argv[1]
    print(eq_case)
    # input will be the output.txt file and will read line no. from start of sols to end of sols, which maps directly to the corresponding variables in the minion file
    #filepath = sys.argv[1] # read and write there
    output=f'./output.txt'
    pointbits = './pointbits.txt'
    # iterate over pointbits.txt for current index and multiple sol val and append that many to the string  

    with open(output) as f:
        with open(pointbits) as p:
            pb = p.read().splitlines()
            #print(pb)
            x = f.read().splitlines()
            #start-1 ; end val
            # x = x[11:267]
            k = 0 
            startidx=11
            while True:
                str_ = ""
                chunk = x[startidx:startidx+256]
                if not chunk or len(chunk) <256:
                    break

                startidx += 261
                print(len(chunk))

                for idx, val in enumerate(chunk):
                    parts = val.split(':')
                    count = int(parts[1])
                    if count==0:
                        pass
                    else:
                        string=pb[idx]
                        multstring = string*count
                        str_ += multstring
                    
                    # print(str_)


                k += 1 
                print(len(str_))
                print('str=', str_)
                with open('./stdinpt.txt', 'w') as kattempt:
                        kattempt.write(str_)
                
            return str_

if __name__ == "__main__":
    main()
