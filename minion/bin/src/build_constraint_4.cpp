// Minion constraint file
#include "minion.h"
#include "../../minion/constraints/reify_true.h"

BUILD_CT(CT_REIFYIMPLY, 1)
#include "minion.h"
#include "../../minion/constraints/reify_true.h"

BUILD_CT(CT_REIFYIMPLY_QUICK, 1)
#include "minion.h"
#include "../../minion/constraints/dynamic_new_and.h"

BUILD_CT(CT_WATCHED_NEW_AND, 0)
#include "minion.h"
#include "../../minion/constraints/dynamic_new_or.h"

BUILD_CT(CT_WATCHED_NEW_OR, 0)
#include "minion.h"
#include "../../minion/constraints/constraint_collect_events.h"

BUILD_CT(CT_COLLECTEVENTS, 1)
