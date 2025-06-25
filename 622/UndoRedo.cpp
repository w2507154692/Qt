#include "UndoRedo.h"

void UndoRedo::UndoAction(void) {
	operation op;
	if (!undoStack.empty()) {
		op = undoStack.top();
		undoStack.pop();
		UndoOp(op);
		if (undoStack.empty())
			undoAction->setEnabled(false);
		else
			undoAction->setEnabled(true);
	}
}

void UndoRedo::RedoAction(void) {
	operation op;
	if (!redoStack.empty()) {
		op = redoStack.top();
		redoStack.pop();
		RedoOp(op);
		if (redoStack.empty())
			redoAction->setEnabled(false);
		else
			redoAction->setEnabled(true);	
	}
}

void UndoRedo::UndoOp(operation op) {
	if (op.type == 1) { //add
		PersonSet::iterator it;
		it = find(set->begin(), set->end(), *op.personList.begin());
		set->erase(it);
		redoStack.push(op);
	}
	else if (op.type == 2) { //delete

		PersonSet::iterator itSet;
		list<Person>::reverse_iterator itPersonList;
		list<int>::reverse_iterator itIndex;

		for (itIndex = op.indexList.rbegin(), itPersonList = op.personList.rbegin();
			itIndex != op.indexList.rend() && itPersonList != op.personList.rend();
			itIndex++, itPersonList++) {
			itSet = set->begin() + *itIndex;
			set->insert(itSet, *itPersonList);
		}
		redoStack.push(op);
	}
	else if (op.type == 3) { //modify
		PersonSet::iterator it;
		// op中的是修改前的人员信息
		operation newOp = op;
		it = find(set->begin(), set->end(), *op.personList.begin());
		*newOp.personList.begin() = *it; //将修改后的人员信息给Redo
		*it = *op.personList.begin(); 
		redoStack.push(newOp);
	}
	redoAction->setEnabled(true);
}

void UndoRedo::RedoOp(operation op) {
	if (op.type == 1) { //add
		set->insert(set->begin() + *op.indexList.begin(), *op.personList.begin());
		undoStack.push(op);
	}
	else if (op.type == 2) { //delete
		list<int>::iterator itIndex;
		for (itIndex = op.indexList.begin(); itIndex != op.indexList.end(); itIndex++)
			set->erase(set->begin() + *itIndex);
		undoStack.push(op);
	}
	else if (op.type == 3) { //modify
		PersonSet::iterator it;
		// op中的是修改后的人员信息
		operation newOp = op;
		it = find(set->begin(), set->end(), *op.personList.begin());
		*newOp.personList.begin() = *it;
		*it = *op.personList.begin();
		undoStack.push(newOp);
	}
	undoAction->setEnabled(true);
}

void UndoRedo::RecordOp(operation op) {
	undoStack.push(op);
	undoAction->setEnabled(true);
	redoAction->setEnabled(false);
	while (!redoStack.empty()) redoStack.pop();
}
