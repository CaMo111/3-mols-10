import sys
import ast 

hmap = {(2, 2, 4, 4, 4): '22444',
        (2, 4, 4, 4, 4): '24446',
        (4, 4, 4, 4, 4): '44444'
        }

PROFILES = [
(2,2,4,4,4),
(2,4,4,4,6),
(4,4,4,4,4)
]

def normalise_profile(profile):
    normalized = [min(x, 10 - x) for x in profile]
    normalised = sorted(normalized)
    norm = tuple(normalised)
    return norm

def main():
    pvs = sys.argv[1]
    pv = ast.literal_eval(pvs)
    ret=f"\n{pv}\n"
    chunks = [tuple(pv[i:i+4]) for i in range(0, 20, 4)]
    
    r1,r2,r3=(),(),()
    for chunk in chunks:
        r1 = r1 + (chunk[1]+chunk[3],)
        r2 = r2 + (chunk[2]+chunk[3],)
        r3 = r3 + (chunk[1]+chunk[2],)
    
    ret += f"R1={hmap[normalise_profile(r1)]}\n"
    ret += f"R2={hmap[normalise_profile(r2)]}\n"
    ret += f"SYMDIFF={hmap[normalise_profile(r3)]}\n"

    print(ret)
    return ret

if __name__ == "__main__":
    main()
