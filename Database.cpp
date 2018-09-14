
#include "Database.h"
#include "Relation.h"
#include "RelationalAl.h"
#include "Graph.h"
#include <map>
#include <string>
#include <vector>
#include <sstream>


using namespace std;

void Database::createRelation(){
    for(unsigned int i = 0; i < mySchemes.size(); i++){
        Predicate scheme = mySchemes[i];
        originalR[scheme.getID()] = Relation(scheme.getID(), scheme.getParameters());
    }
    
    for(unsigned int i = 0; i < myFacts.size(); i++){
        Predicate facts = myFacts[i];
        originalR[facts.getID()].addTuple(facts.getParameters());
    }
}

void makeSelections(Relation &r, const vector<string> &params){
    for(int i = 0; i < (int) params.size(); ++i){
        if(isString(params[i])){
            r = selectValue(r, { i }, {{params[i]}});
        }
        else{
            r = selectIndexes(r, params, i);
        }
    }
    
}

void makeProjections(Relation &r, const vector<string> &params){
    vector<int> projIndexes;
    for(unsigned int i = 0; i < params.size(); ++i){
        if(!isString(params[i])){
            projIndexes.push_back(i);
        }
        else{
        }
    }
    r = rename(r, params, projIndexes);
    r = project(r, projIndexes);
    string s;
}

void Database::printSelections(const Relation &r, Predicate querry){
    vector<string> params;
    cout << querry.getID() << "(";
    params = querry.getParameters();
    for(unsigned int i = 0; i < params.size(); ++i){
        cout << params[i];
        if(i < params.size() - 1){
            cout << ",";
        }
    }
    cout << ")? ";
    if(r.tuples.size() > 0){
        cout << "Yes(" << r.tuples.size() << ")";
    }
    else{
        cout << "No";
    }
    cout << endl;
}

void printProjections(const Relation &r){
    if (r.scheme.size() > 0) {
        for(set<Tuple>::iterator it = r.tuples.begin(); it != r.tuples.end(); ++it){
            vector<string> duplicates;
            string output;
            for(unsigned int i = 0; i < r.scheme.size(); ++i){
                if(!contains(duplicates, r.scheme[i])){
                    output += r.scheme[i] + "=" + it->at(i) + ", ";
                }
                duplicates.push_back(r.scheme[i]);
            }
            cout << "  " << output.substr(0, output.length()-2) << endl;
        }
    }
}

void Database::evalOneRule(set<int> SCC){
    
    for(set<int>::iterator it = SCC.begin(); it != SCC.end(); ++it){
        Rule curRule = myRules[*it];
        printRules(curRule);

        Relation joined;
        Predicate headPred = curRule.headPredicate;
        vector<Predicate> preds = curRule.predicates;
        Relation &head = originalR[curRule.headPredicate.getID()];

        for(unsigned int i = 0; i < preds.size(); ++i){
            Relation r = originalR[preds[i].getID()];

            makeSelections(r, preds[i].getParameters());
            makeProjections(r, preds[i].getParameters());

            if(joined.scheme.size() > 0){
                joined = joinRelations(joined, r);
            }
            else {
                joined = r;
            }
        }
        vector<int> projIndexes;
        for(unsigned int i = 0; i < headPred.getParameters().size(); ++i){
            for(unsigned int j = 0; j < joined.scheme.size(); ++j){
                if(headPred.getParameters()[i] == joined.scheme[j]){
                    projIndexes.push_back(j);
                }
            }
        }
        joined = project(joined, projIndexes);
        joined.setSchemes(head.scheme);
        head = unionRelations(head, joined);
    }
}

void Database::printRules(Rule &r){
    
    vector<string> params;
    cout << r.headPredicate.getID() << "(";
    params = r.headPredicate.getParameters();
    for(unsigned int i = 0; i < params.size(); ++i){
        cout << params[i];
        if(i < params.size() - 1){
            cout << ",";
        }
    }
    cout << ") :- ";
    for(unsigned int i = 0; i < r.predicates.size(); ++i){
        vector<string> params;
        cout << r.predicates[i].getID() << "(";
        params = r.predicates[i].getParameters();
        for(unsigned int j = 0; j < params.size(); ++j){
            cout << params[j];
            if(j < params.size() - 1){
                cout << ",";
            }
        }
        cout << ")";
        if(i < r.predicates.size() - 1){
            cout << ",";
        }
    }
    cout << endl;
}

int Database::numTuples(map<string, Relation> &mapR){
    int tuples = 0;
    
    for(map<string, Relation>::iterator it = mapR.begin(); it != mapR.end(); ++it){
        tuples += it->second.tupleSize();
    }
    return tuples;
}

void Database::buildGraph(){
    
    for(unsigned int i = 0; i < myRules.size(); ++i){
        Node node;
        node.setNodeID(i);
        forwardGraph.insertNode(i, node);
        
        Node reverseNode;
        reverseNode.setNodeID(i);
        reverseGraph.insertNode(i, reverseNode);
    }
  
    for(unsigned int i = 0; i < myRules.size(); ++i){
        for(unsigned int j = 0; j < myRules[i].predicates.size(); ++j){
            for(unsigned int k = 0; k < myRules.size(); ++k){
                if(myRules[i].predicates[j].getID() == myRules[k].headPredicate.getID()){
                    forwardGraph.addAdjNode(i, k);
                    reverseGraph.addAdjNode(k, i);
                }
                if(myRules[i].predicates[j].getID() == myRules[i].headPredicate.getID()){
                    forwardGraph.graphNodes[i].selfDependent = true;
                    reverseGraph.graphNodes[i].selfDependent = true;
                }
            }
        }
    }
    
};

void Database::printDepGraph(){
    cout << "Dependency Graph" << endl;
    const map<int, Node> &nodes = forwardGraph.getGraph();
    for (map<int, Node>::const_iterator iter = nodes.begin(); iter != nodes.end(); ++iter) {
        cout << "R" << iter->first << ":";
        const set<int> &r = iter->second.getAdjList();
        stringstream ss;
        for(set<int>::iterator iter2 = r.begin(); iter2 != r.end(); ++iter2){
            ss << "R" << *iter2 << ",";;
        }
        string str = ss.str();
        cout << str.substr(0, str.length() - 1);
        cout << endl;
    }
};

void Database::createSCCs(){
    
    reverseGraph.dfsForest();
    
    stack<int> stack = reverseGraph.getPON();
    int stackSize = stack.size();
    for(int i = 0; i < stackSize; i++){
        forwardGraph.dfsSCC(stack.top());
        stack.pop();
        if(forwardGraph.SCC.size() > 0){
            forwardGraph.SCCs.push_back(forwardGraph.SCC);
            forwardGraph.SCC.clear();
        }
    }
};

void Database::printMultRules(set<int> SCC){
    unsigned int count = 0;
    for(set<int>::iterator iter = SCC.begin(); iter != SCC.end(); ++iter){
        cout << "R" << *iter ;
        if(count != SCC.size() - 1){
            cout << ",";
        }
        count++;
    }

    
};

void Database::evalSet(set<int> SCC){
    bool noAddedTuples = false;
    bool notSelfDepend = false;

    if(SCC.size() == 1){
        for(set<int>::iterator iter = SCC.begin(); iter != SCC.end(); ++iter){
            if(forwardGraph.graphNodes[*iter].selfDependent != true){
                cout << "SCC: R" << *iter << endl;
                //printRules(myRules[*iter]);
                evalOneRule(SCC);
                notSelfDepend = true;
                
            }
            else{
                cout << "SCC: R" << *iter << endl;
                //printRules(myRules[*iter]);
                //cout << endl;
            }
        }
    }
    
    do{
        
        int tempTupleSize = numTuples(originalR);
        if(!notSelfDepend){
            evalOneRule(SCC);
        }
        int curTupleSize = numTuples(originalR);
        passesInRules++;
        
        if(tempTupleSize == curTupleSize){
            noAddedTuples = true;
        }
    } while(!noAddedTuples);

    cout << passesInRules << " passes: ";
    printMultRules(SCC);
    cout << endl;
    passesInRules = 0;
    
}

void Database::evalRules(){
    
    
    cout << endl;
    cout << "Rule Evaluation" << endl;
    
    for(unsigned int i = 0; i < forwardGraph.SCCs.size(); ++i){
        set<int> SCC = forwardGraph.SCCs[i];
        if(SCC.size() > 1){
            cout << "SCC: ";
            printMultRules(SCC);
            cout << endl;
        }
        evalSet(SCC);
    }
}

void Database::evalQueries(){
    cout << endl;
    cout << "Query Evaluation" << endl;
    for(unsigned int i = 0; i < myQueries.size(); i++){
        Predicate queries = myQueries[i];
        Relation r = originalR[queries.ID];
        
        makeSelections(r, queries.getParameters());
        printSelections(r, queries);
        makeProjections(r, queries.getParameters());
        printProjections(r);
    }
}

