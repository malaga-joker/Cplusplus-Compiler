#include "node.h"
#include<iostream>

using namespace std;

StartNode::StartNode(StatementGroupNode *sg) {
	mSgNode = sg;
}

void StartNode::Interpret() {
	mSgNode->Interpret();
}

StartNode::~StartNode() {
	delete mSgNode;
}

void StatementGroupNode::AddStatement(StatementNode *sn) {
	mStatementNodes.push_back(sn);
}

void StatementGroupNode::Interpret() {
	for (std::vector<StatementNode*>::iterator it=mStatementNodes.begin(); it != mStatementNodes.end(); ++it){
		(*it)->Interpret();
	}
}

StatementGroupNode::~StatementGroupNode() {
	
	for (std::vector<StatementNode*>::iterator it=mStatementNodes.begin(); it != mStatementNodes.end(); ++it)
		delete *it;
}

void CoutStatementNode::addExpression(ExpressionNode *en) {
	mExpressionNodes.push_back(en);
}

void CoutStatementNode::Interpret() {
	for (vector<ExpressionNode*>::iterator it=mExpressionNodes.begin(); it != mExpressionNodes.end(); ++it) {
		if (*it == NULL) {
			cout<<endl;
		}else {
			cout << (*it)->Evaluate();
		}
	}
}

CoutStatementNode::~CoutStatementNode() {
	for (std::vector<ExpressionNode*>::iterator it=mExpressionNodes.begin(); it != mExpressionNodes.end(); ++it)
		delete *it;
}

DeclarationStatementNode::DeclarationStatementNode(IdentifierNode* in){
	mIndentiferNode=in;
}

DeclarationStatementNode::~DeclarationStatementNode(){
	delete mIndentiferNode;
}

AssignmentStatementNode::AssignmentStatementNode(IdentifierNode*in,ExpressionNode* en){
	this->in=in;
	this->en=en;
}

AssignmentStatementNode::~AssignmentStatementNode(){
	delete in;
	delete en;
}

void AssignmentStatementNode::Interpret(){
	int number=en->Evaluate();
    in->setNumber(number);
}

PlusAssignNode::PlusAssignNode(IdentifierNode* in,ExpressionNode* en){
	this->in=in;
	this->en=en;
}

void PlusAssignNode::Interpret(){
	int number=en->Evaluate()+in->Evaluate();
    in->setNumber(number);
}

MinusAssignNode::MinusAssignNode(IdentifierNode* in,ExpressionNode* en){
	this->in=in;
	this->en=en;
}

void MinusAssignNode::Interpret(){
	int number=in->Evaluate()-en->Evaluate();
    in->setNumber(number);
}

MutiAssignNode::MutiAssignNode(IdentifierNode* in,ExpressionNode* en){
	this->in=in;
	this->en=en;
}

void MutiAssignNode::Interpret(){
	int number=en->Evaluate()*in->Evaluate();
    in->setNumber(number);
}

IfStatementNode::IfStatementNode(ExpressionNode* en,StatementNode* sn){
	this->en=en;
	this->sn=sn;
}

IfStatementNode::~IfStatementNode(){
	delete en;
	delete sn;
}

void IfStatementNode::Interpret(){
	if(en->Evaluate())
		sn->Interpret();
}

WhileStatementNode::WhileStatementNode(ExpressionNode* en,StatementNode* sn){
	this->en=en;
	this->sn=sn;
}

WhileStatementNode::~WhileStatementNode(){
	delete en;
	delete sn;
}

void WhileStatementNode::Interpret(){
	while(en->Evaluate())
		sn->Interpret();
}

BinaryOperatorNode::BinaryOperatorNode(ExpressionNode* l,ExpressionNode* r){
    left=l;
	right=r;
}

BinaryOperatorNode::~BinaryOperatorNode(){
	delete left;
	delete right;
}

PlusNode::PlusNode(ExpressionNode * left, ExpressionNode * right) : BinaryOperatorNode(left, right) {
}

int PlusNode::Evaluate() {
	return left->Evaluate() + right->Evaluate();
}

MinusNode::MinusNode(ExpressionNode * left, ExpressionNode * right) : BinaryOperatorNode(left, right) {
}

int MinusNode::Evaluate() {
	return left->Evaluate() - right->Evaluate();
}

MutiNode::MutiNode(ExpressionNode * left, ExpressionNode * right) : BinaryOperatorNode(left, right) {
}

int MutiNode::Evaluate() {
	return left->Evaluate() * right->Evaluate();
}

DiviNode::DiviNode(ExpressionNode * left, ExpressionNode * right) : BinaryOperatorNode(left, right) {
}

int DiviNode::Evaluate() {
	if(right->Evaluate()==0){
		cout<<"Error: divid 0 is not allow!"<<endl;
		return 0;
	}
	else{
	    return left->Evaluate() / right->Evaluate();
	}
}

ModNode::ModNode(ExpressionNode * left, ExpressionNode * right) : BinaryOperatorNode(left, right) {
}

int ModNode::Evaluate() {
	if(right->Evaluate()==0){
		cout<<"Error: divid 0 is not allow!"<<endl;
		return 0;
	}
	else{
	    return left->Evaluate() % right->Evaluate();
	}
}

LessNode::LessNode(ExpressionNode * left, ExpressionNode * right) : BinaryOperatorNode(left, right) {
}

int LessNode::Evaluate() {
	return left->Evaluate() < right->Evaluate();
}

LessEqulNode::LessEqulNode(ExpressionNode * left, ExpressionNode * right) : BinaryOperatorNode(left, right) {
}

int LessEqulNode::Evaluate() {
	return left->Evaluate() <= right->Evaluate();
}

GreaterNode::GreaterNode(ExpressionNode * left, ExpressionNode * right) : BinaryOperatorNode(left, right) {
}

int GreaterNode::Evaluate() {
	return left->Evaluate() > right->Evaluate();
}

GreaterEqulNode::GreaterEqulNode(ExpressionNode * left, ExpressionNode * right) : BinaryOperatorNode(left, right) {
}

int GreaterEqulNode::Evaluate() {
	return left->Evaluate() >= right->Evaluate();
}

EqulNode::EqulNode(ExpressionNode * left, ExpressionNode * right) : BinaryOperatorNode(left, right) {
}

int EqulNode::Evaluate() {
	return left->Evaluate() == right->Evaluate();
}

NotEqulNode::NotEqulNode(ExpressionNode * left, ExpressionNode * right) : BinaryOperatorNode(left, right) {
}

int NotEqulNode::Evaluate() {
	return left->Evaluate() != right->Evaluate();
}

OrNode::OrNode(ExpressionNode * left, ExpressionNode * right) : BinaryOperatorNode(left, right) {
}

int OrNode::Evaluate() {
	return left->Evaluate() || right->Evaluate();
}

AndNode::AndNode(ExpressionNode * left, ExpressionNode * right) : BinaryOperatorNode(left, right) {
}

int AndNode::Evaluate() {
	return left->Evaluate() && right->Evaluate();
}

IntegerNode::IntegerNode(int i) {
	number = i;
}

int IntegerNode::Evaluate() {
	return number;
}

IdentifierNode::IdentifierNode(string name,VariableList* vl){
	this->name = name;
	this->vl = vl;
}

void IdentifierNode::setNumber(int number){
	vl->setNumber(name,number);
}

int IdentifierNode::Evaluate(){
	int number = vl->getNumber(name);
	return number;
}

int EndlNode::Evaluate(){
	cout<<endl;
	return 0;
}