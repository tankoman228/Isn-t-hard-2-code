#include <Blocks.hpp>

void rech(int a, int b) {

		if (((electric[a]->type > 32) && (electric[a]->type < 37)) || ((electric[b]->type > 32) && (electric[b]->type < 37))) { return; }

	/*	else { if ((electric[a]->type == 32 || electric[b]->type == 32) && (rand()%2 == 0)) { return; } }*/

		if (electric[a]->charge == electric[b]->charge) { return; }

		if (electric[a]->charge > electric[b]->charge) {
			electric[b]->charge++;
			electric[a]->charge -= 1;

			if (electric[a]->charge > electric[b]->charge + 1) {
				electric[b]->charge += 2;
				electric[a]->charge -= 2;
			}
			return;
		}

		electric[b]->charge -= 1;
		electric[a]->charge++;
		if (electric[a]->charge + 1 > electric[b]->charge) { return; }
		electric[b]->charge -= 2;
		electric[a]->charge += 2;

	}
void rech(Electric& a, Electric& b) {

	if (((a.type > 32) && (a.type < 37)) || ((b.type > 32) && (b.type < 37))) { return; }

	/*	else { if ((electric[a]->type == 32 || electric[b]->type == 32) && (rand()%2 == 0)) { return; } }*/

	if (a.charge == b.charge) { return; }

	if (a.charge > b.charge) {
		b.charge++;
		a.charge -= 1;

		if (a.charge > b.charge + 1) {
			b.charge += 2;
			a.charge -= 2;
		}
		return;
	}

	b.charge -= 1;
	a.charge++;
	if (a.charge + 1 > a.charge) { return; }
	b.charge -= 2;
	a.charge += 2;

}
void rech(Electric& a, int c) {

	Electric& b = *electric[c];

	if (((a.type > 32) && (a.type < 37)) || ((b.type > 32) && (b.type < 37))) { return; }

	/*	else { if ((electric[a]->type == 32 || electric[b]->type == 32) && (rand()%2 == 0)) { return; } }*/

	if (a.charge == b.charge) { return; }

	if (a.charge > b.charge) {
		b.charge++;
		a.charge -= 1;

		if (a.charge > b.charge + 1) {
			b.charge += 2;
			a.charge -= 2;
		}
		return;
	}

	b.charge -= 1;
	a.charge++;
	if (a.charge + 1 > a.charge) { return; }
	b.charge -= 2;
	a.charge += 2;

}
void rech_give_charge(int a) {
	if (electric[a]->charge < 58) { electric[a]->charge += 2; }
}