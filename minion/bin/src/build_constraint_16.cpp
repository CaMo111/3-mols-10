// Minion constraint file
#include "minion.h"
#include "../../minion/constraints/constraint_equal.h"

BUILD_CT(CT_MINUSEQ, 2)
#include "minion.h"
#include "../../minion/constraints/constraint_gacequal.h"

BUILD_CT(CT_GACEQ, 2)
#include "minion.h"
#include "../../minion/constraints/dynamic_less.h"

BUILD_CT(CT_WATCHED_LESS, 2)
#include "minion.h"
#include "../../minion/constraints/dynamic_neq.h"

BUILD_CT(CT_WATCHED_NEQ, 2)
#include "minion.h"
#include "../../minion/constraints/constraint_less.h"

BUILD_CT(CT_INEQ, 2)
