#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <climits>
#include <cmath>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <algorithm>
#include "row.hpp"


double accuracy(std::vector<Row> set, std::vector<int> curr_set, int to_add) {
	double correct = 0;
	double tot_correct = 0;	
	double dist = 0;
	int n_loc = 0;
	int n_label = 0;
	bool within = false;
    
	for(int i = 0; i < set.size(); ++i) {
	        double s_dist = INT_MAX;
		Row temp;
        
	        for(int j = 0; j < set.size(); ++j) {
			if(j != i) {
				dist = 0.0;
				for(unsigned z = 0; z < set.at(0).features.size(); ++z) {
					within = false;
					for(unsigned fml = 0; fml < curr_set.size(); ++fml) {
						if(curr_set.at(fml) == z) {
							within = true;
						}
					}
					if(z == to_add || within == true) {
						dist += pow(set.at(i).features.at(z) - set.at(j).features.at(z), 2);
					}
				}
				if(dist < s_dist) {
					s_dist = dist;
					temp = set.at(j);
					n_loc = j;
					n_label = set.at(j).fclass;
				}
			}
		}
    
		if(temp.fclass == set.at(i).fclass) {
			correct += 1;
		}
		tot_correct += 1;
	}
	return (correct/tot_correct);
}

double accuracy(std::vector<Row> set, std::vector<int> curr_set) {
        double correct = 0;
        double tot_correct = 0;
        double dist = 0;
        int n_loc = 0;
        int n_label = 0;
        bool within = false;

        for(int i = 0; i < set.size(); ++i) {
                double s_dist = INT_MAX;
                Row temp;

                for(int j = 0; j < set.size(); ++j) {
                        if(j != i) {
                                dist = 0.0;
                                for(unsigned z = 0; z < set.at(0).features.size(); ++z) {
                                        within = false;
                                        for(unsigned fml = 0; fml < curr_set.size(); ++fml) {
                                                if(curr_set.at(fml) == z) {
                                                        within = true;                                                                                               }
                                        }
                                        if(within == true) {
                                                dist += pow(set.at(i).features.at(z) - set.at(j).features.at(z), 2);
                                        }
                                }
                                if(dist < s_dist) {
                                        s_dist = dist;
                                        temp = set.at(j);
                                        n_loc = j;
                                        n_label = set.at(j).fclass;
                                }
                        }
                }

                if(temp.fclass == set.at(i).fclass) {
                        correct += 1;
                }
                tot_correct += 1;
        }
        return (correct/set.size());
}


/*double accuracy(std::vector<Row> set) {
        double correct = 0;

        double dist = 0;
        int n_loc = 0;
        int n_label = 0;
        bool within = false;

        for(int i = 0; i < set.size(); ++i) {
                double s_dist = INT_MAX;
                Row temp;

                for(int j = 0; j < set.size(); ++j) {
                        if(j != i) {
                                dist = 0.0;
                                for(unsigned z = 0; z < set.at(0).features.size(); ++z) {
                                                dist += pow(set.at(i).features.at(z) - set.at(j).features.at(z), 2);
                                        
                                }
                                if(dist < s_dist) {
                                        s_dist = dist;
                                        temp = set.at(j);
                                        n_loc = j;
                                        n_label = set.at(j).fclass;
                                }
                        }
                }                                                                                                    
                if(temp.fclass == set.at(i).fclass) {
                        correct += 1;
                }
        }
        return (correct/set.size());
}*/

void feature_search_demo(std::vector<Row> set) {
	std::vector<int> curr_features;
	std::vector<int> best_features;
	int to_add1;
	std::vector<int> to_add;
	double best_acc = 0;
	double acc = 0;
	double true_max = 0;
	bool boo = true;
	for(unsigned i = 0; i < set.at(0).features.size(); ++i) {
		std::cout << "On the " << i << " level of the search tree" << std::endl;
		

		for(unsigned k = 0; k < set.at(0).features.size(); ++k) {
			for(unsigned i = 0; i < curr_features.size(); ++i) {
				if( k == curr_features.at(i) ) {
					boo = false;
				}
			}
			if(boo == true) {
				std::cout << "--Considering adding the " << k << " feature\n";
				acc = accuracy(set, curr_features, k);
				std::cout << "accuracy of " << acc << "\n";
				if( acc > best_acc ) {
					best_acc = acc;
					to_add1 = k;
					if(acc > true_max) {
						best_features.clear();
						true_max = acc;
						best_features = curr_features;
						best_features.push_back(to_add1);
						
					}
				}
			}
			boo = true;
		}
		best_acc = 0;
		curr_features.push_back(to_add1);
		std::cout << "On level " << i << " I added feature " << to_add1 << " to current set\n";
		std::cout << "Current features are: ";
		for(unsigned aa = 0; aa < curr_features.size(); ++aa) {
			std::cout << curr_features.at(aa) << " ";
		}
	}
	
	std::cout << "\nhighest accuracy total: " << true_max;
	std::cout << "\nusing feature set: ";
	for(unsigned i = 0; i < best_features.size(); ++i) {
		std::cout << best_features.at(i) << ", ";
	}
	

}

void backwards_elim(std::vector<Row> set) {
        std::vector<int> curr_features;
	for(unsigned i = 0; i < set.at(0).features.size(); ++i) {
		curr_features.push_back(i);
	}

	std::cout << "curr feature should have every feature: \n";
	
	for(unsigned i = 0; i < curr_features.size(); ++i) { 
		std::cout << curr_features.at(i) << "\n";
	}


        std::vector<int> best_features;
	std::vector<int> tmp_features;
	std::vector<int> tmp_features1;
        int to_add1;
	int to_sub_loc;
        std::vector<int> to_sub;
	std::vector<int>::iterator it;
        double best_acc = 0;
        double acc = 0;
        double true_max = 0;
        bool boo = true;
	unsigned int index = 0;
        for(unsigned i = 0; i < set.at(0).features.size(); ++i) {
                std::cout << "On the " << i << " level of the search tree" << std::endl;
                for(unsigned k = 0; k < set.at(0).features.size(); ++k) {
                        for(unsigned i = 0; i < curr_features.size(); ++i) {
                                if( k == curr_features.at(i) ) {
                                        boo = false;
                                }
                        }
                        if(boo == false) {
                                std::cout << "--Considering removing the " << k << " feature\n";
				tmp_features.clear();
				for(unsigned tmp = 0; tmp < curr_features.size(); ++tmp) {
					if(curr_features.at(tmp) != k) {
						tmp_features.push_back(curr_features.at(tmp));
					}
				}
                                acc = accuracy(set, tmp_features);
                                std::cout << "accuracy of " << acc << "\n";
                                if( acc > best_acc ) {                                                                                                       best_acc = acc;
                                        to_add1 = k;
					tmp_features1 = tmp_features;
					/*tmp_features.clear();
					for(unsigned tmp = 0; tmp < curr_features.size(); ++tmp) {
						if(tmp != k) {
							tmp_features.push_back(curr_features.at(tmp));
						}
					}*/
                                        if(acc > true_max) {
                                                best_features.clear();
                                                true_max = acc;
                                                best_features = tmp_features1;
                                        }
                                }
                        }
                        boo = true;
                }
                best_acc = 0;
		curr_features.clear();
		curr_features = tmp_features1;
		

                std::cout << "On level " << i << " I removed feature " << to_add1 << " to current set\n";
                std::cout << "Current features are: ";
                for(unsigned aa = 0; aa < curr_features.size(); ++aa) {
                        std::cout << curr_features.at(aa) << " ";
                }
        }

        std::cout << "\nhighest accuracy total: " << true_max;
        std::cout << "\nusing feature set: ";
        for(unsigned i = 0; i < best_features.size(); ++i) {
                std::cout << best_features.at(i) << ", ";
        }


}



int main() {
	std::vector<Row> to_insert;


	std::ifstream inFS;
	inFS.open("Small_data_68.txt");
//	inFS.open("Large39.txt");
	if(!inFS) {
		std::cout << "Error opening file\n";
		return -1;
	}
	std::string line;
	float feature;
	float temp;
	Row row_temp;
	int counter = 1;
	while(getline(inFS, line)) {
		std::stringstream sstream(line);
		sstream >> feature;
		row_temp.fclass = feature;
		while(sstream >> feature) {
			row_temp.features.push_back(feature);
		}
		to_insert.push_back(row_temp);
		row_temp.features.clear();
	}




//	feature_search_demo(to_insert);
	backwards_elim(to_insert);
//	std::cout << "everything inside " << accuracy(to_insert);
}
