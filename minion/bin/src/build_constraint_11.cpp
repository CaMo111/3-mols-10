// Minion constraint file
#include "minion.h"
#include "../../minion/constraints/constraint_mddc.h"

BUILD_CT(CT_NEGATIVEMDDC, 1)
#include "minion.h"
#include "../../minion/constraints/constraint_shortstr2.h"

BUILD_CT(CT_STR, 1)
#include "minion.h"
#include "../../minion/constraints/constraint_min.h"

BUILD_CT(CT_MAX, 2)
#include "minion.h"
#include "../../minion/constraints/constraint_min.h"

BUILD_CT(CT_MIN, 2)
#include "minion.h"
#include "../../minion/constraints/constraint_nvalue.h"

BUILD_CT(CT_GEQNVALUE, 2)
