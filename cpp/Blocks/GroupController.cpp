#include <Blocks.h>

bool* TargetGroupController::getTarget() {

	if (target == a) {
		return dmode;
	}
	if (target == b) {
		return crystal;
	}
	if (target == c) {
		return lmode;
	}
	if (target == barmode) {
		return barmode;
	}
}

int TargetGroupController::getGroup() {
	return group;
}