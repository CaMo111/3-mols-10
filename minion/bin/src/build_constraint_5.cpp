// Minion constraint file
#include "minion.h"
#include "../../minion/constraints/constraint_gacalldiff.h"

BUILD_CT(CT_GACALLDIFF, 1)
#include "minion.h"
#include "../../minion/constraints/constraint_neq.h"

BUILD_CT(CT_ALLDIFF, 1)
#include "minion.h"
#include "../../minion/constraints/constraint_alldiffmatrix.h"

BUILD_CT(CT_ALLDIFFMATRIX, 1)
#include "minion.h"
#include "../../minion/constraints/dynamic_sum.h"

BUILD_CT(CT_WATCHED_GEQSUM, 1)
#include "minion.h"
#include "../../minion/constraints/dynamic_sum.h"

BUILD_CT(CT_WATCHED_LEQSUM, 1)
