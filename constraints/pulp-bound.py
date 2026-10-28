import pulp
import sys
import ast 
import math

# should take file path as a systme argument and write from there
# ie 'python3 pulp-bound.py ./consistent.min'
def main():
    filepath = sys.argv[1] # read and write there 
    print(filepath)


    model = pulp.LpProblem(name="system", sense=pulp.LpMaximize)
    lp = {}

    with open(filepath) as f:
        for line in f:
            if line[:5] == 'BOUND':
                # from consistent.min file will read all variables and add them to the model 
                parts = line.split()
                bounds_str = parts[2].strip("{}")  # '0..16'
                _, high_str = bounds_str.split("..")  # ['0', '16']
                high = int(high_str)
                lp[parts[1]]= pulp.LpVariable(parts[1], lowBound=0, upBound=high, cat='Integer')

            if line[:6] == 'sumgeq': #  or line[:6] == 'sumleq' <- dont need to bother with this since pulp has a eq method 
                commasep = line[8:-2]
                var, val = commasep.split("],")
                var_list = var.split(",")

                model += (pulp.lpSum([lp[v] for v in var_list]) == int(val))
        
    solver = pulp.PULP_CBC_CMD(msg=False)
    bounds_changed = True
    pass_num = 1

    while bounds_changed:
        bounds_changed = False
        print(f"--- Starting Bound Tightening Pass {pass_num} ---")

        for var_name, var_obj in lp.items():
            model.sense = pulp.LpMinimize
            model.setObjective(var_obj)
            model.solve(solver)

            if model.status == pulp.LpStatusOptimal:
                min_val = math.ceil(pulp.value(var_obj))
                if min_val > var_obj.lowBound:
                    var_obj.lowBound = min_val
                    bounds_changed = True

            model.sense = pulp.LpMaximize
            model.setObjective(var_obj)
            model.solve(solver)

            if model.status == pulp.LpStatusOptimal:
                max_val = math.floor(pulp.value(var_obj))
                if max_val < var_obj.upBound:
                    var_obj.upBound = max_val
                    bounds_changed = True

        pass_num += 1

    print("\n--- Final Tightened Bounds ---")

    # instead should write these back into consistent.min lines 3:258 inclusive
    with open(filepath, 'r') as f: 
        file_lines = f.readlines()
    idx=2

    for var_name, var_obj in lp.items():
        nl = f"BOUND {var_name} {{{var_obj.lowBound}..{var_obj.upBound}}}\n"
        file_lines[idx] = nl
        idx += 1 
        # replace consistent.min at line[idx] with nl
        # print(f"BOUND {var_name} {{{var_obj.lowBound}..{var_obj.upBound}}}")
        print(nl.strip())

    with open(filepath, 'w') as f:
        f.writelines(file_lines)
        
    print("\nFile successfully updated.")

if __name__ == "__main__":
    main()
