#include "processor.h"

// Constructor
Processor::Processor(std::vector<ASTNode> a, std::string b) 
{

	nodes = a;
	filename = b;

}

bool needsLine(std::string type) {
	if(type == "FOR" || type == "WHILE" || type == "FUNCTION") return false;
	return true;
}

void Processor::dfs(int cur) {

	if(nodes[cur].type == "PROGRAM") {
	    for(int z : nodes[cur].children) {
	        dfs(z);
	        if(needsLine(nodes[z].type)) outfile << ';';
	       	outfile << '\n';
	    }
	    return;
	}

	if(nodes[cur].type == "FUNCTION") {

		outfile << nodes[cur].varType << " ";
		outfile << nodes[cur].name;

		if(nodes[cur].children.size() != 2) {
			std::cout << "ERROR: bad function node" << std::endl;
			return;
		}

		int child1 = nodes[cur].children[0];
		int child2 = nodes[cur].children[1];

		outfile << "(";
		int i = 0;
	    for(int z : nodes[child1].children) {
	        dfs(z);
	        i++;
	        if(i != nodes[child1].children.size()) outfile << ',';
	    }
		outfile << ")";

		outfile << "{\n";
	    for(int z : nodes[child2].children) {
	        dfs(z);
	        if(needsLine(nodes[z].type)) outfile << ';';
	       	outfile << '\n';
	    }
		outfile << "}\n";
	    return;
	}

	if(nodes[cur].type == "FUNCTION CALL") {


		if(nodes[cur].children.size() != 2) {
			std::cout << "ERROR: bad function node" << std::endl;
			return;
		}

		int child1 = nodes[cur].children[0];
		int child2 = nodes[cur].children[1];

		outfile << nodes[child1].name << "(";

		int i = 0;
	    for(int z : nodes[child2].children) {
	        dfs(z);
	        i++;
	        if(i != nodes[child2].children.size()) outfile << ',';
	    }
		outfile << ")";
	    return;
	}

	if(nodes[cur].type == "FOR") {

		outfile << "for(";
		if(nodes[cur].children.size() != 4) {
			std::cout << "ERROR: bad function node" << std::endl;
			return;
		}

		int child1 = nodes[cur].children[0];
		int child2 = nodes[cur].children[1];
		int child3 = nodes[cur].children[2];
		int child4 = nodes[cur].children[3];


	    dfs(child1);
		outfile << ";";
	    dfs(child2);
		outfile << ";";
	    dfs(child3);
	    outfile << "){\n";
	    for(int z : nodes[child4].children) {
	        dfs(z);
	        if(needsLine(nodes[z].type)) outfile << ';';
	       	outfile << '\n';
	    }
	    outfile << "}"; 
	    return;
	}

    if(nodes[cur].type == "FORN"){
        outfile << "for(";
        if(nodes[cur].children.size() != 3) {
            std::cout << "ERROR: bad function node" << std::endl;
            return;
        }
        int child1 = nodes[cur].children[0];
        int child2 = nodes[cur].children[1];
        int child3 = nodes[cur].children[2];

        //forn(i, n) { //iterate i from 0 to n-1, equal to for(int i = 0; i < n;
        //i++) 
        outfile << "int " << nodes[child1].name << " = 0; ";
        outfile << nodes[child1].name << " < ";
        dfs(child2);
        outfile << "; ";
        outfile << nodes[child1].name << "++){\n";
        for(int z : nodes[child3].children) {
            dfs(z);
            if(needsLine(nodes[z].type)) outfile << ';';
            outfile << '\n';
        }
        outfile << "}";
        return;
    }

    if(nodes[cur].type == "WHILE") {
        outfile << "while(";
        if(nodes[cur].children.size() != 2) {
            std::cout << "ERROR: bad function node" << std::endl;
            return;
        }
        int child1 = nodes[cur].children[0];
        int child2 = nodes[cur].children[1];
        dfs(child1);
        outfile << "){\n";

        for(int z: nodes[child2].children) {
            dfs(z);
            if(needsLine(nodes[z].type)) outfile << ';';
            outfile << '\n';
        }
        outfile << "}";
        return;

    }

	if(nodes[cur].type == "DECLARATION") {
		outfile << nodes[cur].varType << ' ' << nodes[cur].name;

		if(nodes[cur].children.size()) {

			outfile << " = ";
			dfs(nodes[cur].children[0]);
		}
	    return;
	}


	if(nodes[cur].type == "IDENTIFIER") {
		outfile << nodes[cur].name;
		if(nodes[cur].children.size()) {

			outfile << " = ";
			dfs(nodes[cur].children[0]);
		}
	    return;
	}

    if(nodes[cur].type == "POSTFIX OPERATOR") {
        if(nodes[cur].children.size() != 1) {
            std::cout << "ERROR: bad function node" << std::endl;
            return;
        }
        // For postfix operators like i++, the operand (child) should come first
        dfs(nodes[cur].children[0]);
        outfile << nodes[cur].name; // Print the '++' after the operand
        return;
    }


	if(nodes[cur].type == "RETURN") {
		outfile << "return ";
		if(nodes[cur].children.size()) {
			dfs(nodes[cur].children[0]);
		}
	    return;
	}

	if(nodes[cur].type == "UNARY OPERATOR") {
		outfile << nodes[cur].name;
		if(nodes[cur].children.size()) {
			dfs(nodes[cur].children[0]);
		}
	    return;
	}

	if(nodes[cur].type == "INT_LITERAL") {
		outfile << nodes[cur].name;
	    return;
	}



	if(nodes[cur].type == "BINARY OPERATOR") {
		if(nodes[cur].children.size() != 2) {
			std::cout << "ERROR: bad function node" << std::endl;
			return;
		}

		int child1 = nodes[cur].children[0];
		int child2 = nodes[cur].children[1];

		outfile << "(";
		dfs(child1);
		outfile << " " << nodes[cur].name << " ";
		dfs(child2);
		outfile << ")";
	    return;
	}


	if(nodes[cur].type == "IDENTIFIER") {
		outfile << nodes[cur].name;
	    return;
	}

    if(nodes[cur].type == "COUT") {
        if(nodes[cur].children.size() != 1) {
            std::cout << "ERROR: COUT node should have exactly one child.\n";
            return;
        }

        outfile << "std::cout << ";
        int child = nodes[cur].children[0];

        if (nodes[child].type == "IDENTIFIER") {
            outfile << nodes[child].name;
        } else if (nodes[child].type == "STRING_LITERAL") {
            // If parser puts the quotes in nodes[child].name:
            outfile << nodes[child].name;
        } else {
            std::cout << "ERROR: COUT node child is neither IDENTIFIER nor STRING_LITERAL.\n";
            return;
        }

        outfile << " << '\\n'";
        return;
    }




    // for(int i = 0; i < depth; i++) {
    //     cout << "|";
    //     if(i < depth-1) cout << "  ";
    // }

    // if(depth) cout << "--";
    
    // if(nodes[cur].type.size()) cout << nodes[cur].type << ' ';
    // else cout << "- ";
    // if(nodes[cur].varType.size()) cout << nodes[cur].varType << ' ';
    // else cout << "- ";

    // cout <<  nodes[cur].name << '\n';
    // for(int z : nodes[cur].children) {
    //     dfs(z, depth+1);
    // }
}

void Processor::process() {

    outfile = std::ofstream(filename);

    outfile << "#include <string>\n#include <vector>\nusing namespace std;\n#include <iostream>\n";
	outfile << "typedef long long ll;\ntypedef vector<int> vi;\nbool multiTest = 0;\n";
	outfile << "ll d, l, r, k, n, m, p, q, u, v, w, x, y, z;\n";
	dfs(0);

	outfile << "int main() {\nint t = 1;\nif (multiTest) cin >> t;\nfor (int ii = 0; ii < t; ii++) {solve(ii);} \n return 0;\n}";


}