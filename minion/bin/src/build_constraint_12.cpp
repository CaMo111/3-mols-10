// Minion constraint file
#include "minion.h"
#include "../../minion/constraints/constraint_nvalue.h"

BUILD_CT(CT_LEQNVALUE, 2)
#include "minion.h"
#include "../../minion/constraints/sum_constraints/constraint_sum.h"

BUILD_CT(CT_GEQSUM, 2)
#include "minion.h"
#include "../../minion/constraints/sum_constraints/constraint_sum.h"

BUILD_CT(CT_LEQSUM, 2)
#include "minion.h"
#include "../../minion/constraints/constraint_element.h"

BUILD_CT(CT_ELEMENT, 3)
#include "minion.h"
#include "../../minion/constraints/constraint_element.h"

BUILD_CT(CT_ELEMENT_ONE, 3)
