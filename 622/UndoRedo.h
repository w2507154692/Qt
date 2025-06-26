#pragma once
#include "stack"
#include "list"
#include "PersonSet.h"
#include "QAction"

typedef struct {
	short type; //1-添加，2-删除，3-修改
	list<Person> personList;
	list<int> indexList; //对应位置索引（可选）
}operation;

class UndoRedo
{
public:
	void UndoAction(void);
	void RedoAction(void);
	void UndoOp(operation op);
	void RedoOp(operation op);
	void RecordOp(operation op);

public:
	stack<operation> undoStack;
	stack<operation> redoStack;
	QAction* undoAction;
	QAction* redoAction;

	PersonSet* set;
};

