#pragma once
#include "stack"
#include "list"
#include "PersonSet.h"
#include "QAction"

typedef struct {
	short type; //1-��ӣ�2-ɾ����3-�޸�
	list<Person> personList;
	list<int> indexList; //��Ӧλ����������ѡ��
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

