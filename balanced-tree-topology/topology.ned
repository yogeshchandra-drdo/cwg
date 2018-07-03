//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

// Created: 2015-3-14 for project network-ass

package network_ass;

import ned.DelayChannel;

     

simple Node {
    parameters:
        @display("i=misc/node_vs");
    gates:
        input parent @loose;
        output left @loose;
        output right @loose;
    
}


simple Tree {
	parameters:
		int node_num;
    gates:
        inout in @loose;
        inout out @loose;
     //connections:
     	
}

network Topology
{
    parameters:
    	@display("i=misc/node_vs");
    submodules:
        //dummy_node: Node;
    	avl_tree: Tree;
    
    //connections:
    	//avl_tree.out <--> {delay=10ms;} <--> avl_tree.in;
    	//avl_tree.in <-- {delay=100ms;} <-- avl_tree.out;
}
