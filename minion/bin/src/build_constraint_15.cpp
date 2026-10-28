// Minion constraint file
#include "minion.h"
#include "../../minion/constraints/unary/dynamic_notinrange.h"

BUILD_CT(CT_WATCHED_NOT_INRANGE, 1)
#include "minion.h"
#include "../../minion/constraints/unary/dynamic_notinset.h"

BUILD_CT(CT_WATCHED_NOT_INSET, 1)
#include "minion.h"
#include "../../minion/constraints/constraint_abs.h"

BUILD_CT(CT_ABS, 2)
#include "minion.h"
#include "../../minion/constraints/constraint_equal.h"

BUILD_CT(CT_DISEQ, 2)
#include "minion.h"
#include "../../minion/constraints/constraint_equal.h"

BUILD_CT(CT_EQ, 2)
