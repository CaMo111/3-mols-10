import sys

def main():
    glob= sys.argv[1]
    sep = glob.split('X')[1:]

    sep_ = [f"X{item}" for item in sep]

    ret=''

    sep__ = f"[{','.join(sep_)}]"


    ret+=f'sumgeq({sep__},100)\n'
    ret+=f'sumleq({sep__},100)'

    print(ret)
    return ret

if __name__ == "__main__":
    main()