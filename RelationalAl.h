
#ifndef RelationalAl_h
#define RelationalAl_h
#include <stdio.h>
#include <string>
#include "Relation.h"
#include "Scheme.h"
#include <vector>



using namespace std;

const int NOT_JOINABLE_TUPLES = -1;
const int NO_COMMON_SCHEMES = -2;


inline bool isString(string parameter){
    return parameter.length() > 0 && parameter[0] == '\'';
}

inline vector<Tuple> getDuplicates(const Relation &r, int index1, int index2){
    vector<Tuple> duplicates;
    for(set<Tuple>::iterator it = r.tuples.begin(); it != r.tuples.end(); ++it){
        if(it->at(index1) == it->at(index2)){
            duplicates.push_back( {it->at(index1), it->at(index2)} );
        }
    }
    return duplicates;
}

inline bool contains(vector<string> params, string value){
    for(unsigned int i = 0; i < params.size(); ++i){
        if(params[i] == value){
            return true;
        }
    }
    return false;
}


inline Relation selectValue(const Relation &r, vector<int> indexes, vector<Tuple> values){
    Relation newR;
    newR.setName(r.name);
    newR.setSchemes(r.scheme);
    
    for(set<Tuple>::iterator it = r.tuples.begin(); it != r.tuples.end(); ++it){
        for(unsigned int i = 0; i < values.size(); ++i){
            bool correctParams = true;
            for(unsigned int j = 0; j < indexes.size(); ++j){
                if(!contains(values[i], it->at(indexes[j]))){
                    correctParams = false;
                    break;
                }
            }
            if(correctParams == true){
                newR.addTuple(*it);
            }
        }
    }
    
    return newR;
}

inline Relation project(const Relation &r, vector<int> indexes){
    Relation newR;
    newR.setName(r.name);
    
    
    for(unsigned int i = 0; i < indexes.size(); ++i){
        newR.addScheme(r.scheme[indexes[i]]);
    }

    for(set<Tuple>::iterator it = r.tuples.begin(); it != r.tuples.end(); ++it){
        Tuple newtuple;
        for(unsigned int i = 0; i < indexes.size(); ++i){
            newtuple.push_back(it->at(indexes[i]));
        }
        newR.addTuple(newtuple);
    }

    return newR;
}

inline Relation rename(const Relation &r, Scheme s, vector<int> projIndexes){
    Relation newR;
    newR.setName(r.name);
    newR.setSchemes(r.scheme);
    for(unsigned int i = 0; i < projIndexes.size(); ++i){
        newR.scheme[projIndexes[i]] = s[projIndexes[i]];
    }
    newR.tuples = r.tuples;

    return newR;
}

inline Relation selectIndexes(Relation r, vector<string> params, int index1){
    int indexDup = -1;
    for(int i =  0; i < index1; ++i){
        if(params[index1] == params[i]){
            indexDup = i;
        }
        
    }
    if(indexDup >=  0){
        vector<Tuple> dupls = getDuplicates(r, indexDup, index1);
        return selectValue(r, { indexDup, index1 }, dupls);
    }
    return r;
}

inline void printAddedTuples(const Tuple &t, const Relation &r1){
    cout << "  ";
    for(unsigned int i = 0; i < t.size(); ++i){
        cout << r1.scheme[i] << "=" << t.at(i);
        if(i < t.size() - 1){
            cout << ", ";
        }
    }
    cout << endl;
}

inline Relation unionRelations(const Relation &r1, const Relation &r2){
    Relation r = r1;
    if(r1.getScheme() == r2.getScheme()){
        set<Tuple> tuple = r2.getTuples();
        for(set<Tuple>::iterator it = tuple.begin(); it != tuple.end(); ++it){
            if(r.addTuple(*it)){
                printAddedTuples(*it, r1);
            }
        }
    }
    return r;
}

inline Tuple joinTuples(const Tuple &t1,const Tuple &t2, vector<pair<int, int> > &dupIndexes){
    Tuple joined = t1;
    for(unsigned int i = 0; i < dupIndexes.size(); ++i){
        if(t1[dupIndexes[i].first] != t2[dupIndexes[i].second]){
            return Tuple();
        }
        else{
            //t2.erase(t2.begin() + dupIndexes[i].second);
        }
    }
    
    for(unsigned int i = 0; i < t2.size(); ++i){
        bool contains = false;
        for(unsigned int j = 0; j < dupIndexes.size(); ++j){
            if((int) i == dupIndexes[j].second){
                contains = true;
                break;
            }

        }
        if(!contains){
            joined.push_back(t2[i]);
        }
    }
    return joined;
}

inline vector<pair<int,int> > getDupIndexes(Relation &r1, Relation &r2){
    vector<pair<int, int> > dupIndexes;
    for(unsigned int i = 0; i < r1.scheme.size(); ++i){
        for(unsigned int j = 0; j < r2.scheme.size(); ++j){
            if(r1.scheme[i] == r2.scheme[j]){
                dupIndexes.push_back(pair<int,int>(i, j));
            }
        }
    }
    return dupIndexes;
}

inline vector<string> newSchemes(Relation &r1, Relation &r2){
    Scheme newSchema = r1.scheme;
    for(unsigned int i = 0; i < r2.scheme.size(); ++i){
        if(!contains(newSchema, r2.scheme[i])){
            newSchema.push_back(r2.scheme[i]);
        }
    }
    return newSchema;
}

inline bool joinable(const Tuple &t1, const Tuple &t2, const Scheme &s1, const Scheme &s2){
    for(unsigned int i = 0; i < s1.size(); ++i){
        for(unsigned int j = 0; j < s2.size(); ++j){
            if(s1[i] == s2[j]){
                if( t1[i] != t2[j]){
                    return false;
                }
            }
        }
    }
    return true;
}

inline Relation joinRelations(Relation &r1, Relation &r2){
    if(r1.scheme.size() <= 0){
        return r2;
    }
    if(r2.scheme.size() <= 0){
        return r1;
    }
    
    Relation joined;
    joined.setSchemes(newSchemes(r1,r2));
    vector<pair<int, int> > dupIndexes = getDupIndexes(r1, r2);
    
    for(set<Tuple>::iterator it = r1.tuples.begin(); it != r1.tuples.end(); ++it){
        //Tuple t1 = *it;
       for(set<Tuple>::iterator it2 = r2.tuples.begin(); it2 != r2.tuples.end(); ++it2){
           
           //Tuple t2 = *it2;
           Tuple t = joinTuples(*it, *it2, dupIndexes);
           if(t.size() > 0){
               joined.addTuple(t);
           }
           
        }
    }
    return joined;
}





#endif /* RelationalAl_h */
