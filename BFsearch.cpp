#include "BFsearch.h"

template <class S>
unsigned long long int BFsearch<S>::open2close() {
	if (!this->open.empty()) {
		this->Sn = this->open.front();
		this->open.pop();
		this->graph[this->Sn] = 1;
		this->Sn->setNum(this->n);
		this->n++;
		return this->n;
	}
	return 0;
}

template <class S>
bool BFsearch<S>::generate() {
	bool is_successful = this->Sn.generate(this->M);
	if (is_successful)
	{
		for (auto i = this->M.begin(); i != this->M.end(); i++) {
			this->open.push(*i);
		}
	}
	return is_successful;
}

template <class S>
void BFsearch<S>::changeM() {
	for (auto i = this->M.begin(); i != this->M.end(); i++) {
		i->setParent(this->Sn);
	}
}

template <class S>
bool BFsearch<S>::search(std::stack<S*>& states) {
	this->open.push(this->start);
	while (true) {
		if (this->open.empty())
			return false;
		this->open2close();
		if (this->Sn == this->target) {
			S* curr = this->Sn;
			while (curr != NULL)
			{
				states.push(curr);
				curr = curr->getParent();
			}
			return true;
		}
		if (this->generate())
			this->changeM();
	}
}
