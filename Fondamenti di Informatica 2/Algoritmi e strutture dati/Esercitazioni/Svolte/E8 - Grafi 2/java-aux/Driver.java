import java.util.LinkedList;
import java.util.List;

public class Driver {

    public static void print() {
        System.out.println("Richiesto argomento: {graph, sweep, top_sort, strong_cc}");
    }

    public static void main(String[] argv) {

        if (argv.length < 1) {
            print();
            return;
        }
        
        if (argv[0].equals("graph")) {
            Graph<String> graph = new Graph<String>();

            Graph.GraphNode<String> a = graph.addNode("a");
            Graph.GraphNode<String> b = graph.addNode("b");
            Graph.GraphNode<String> c = graph.addNode("c");
            Graph.GraphNode<String> d = graph.addNode("d");
            Graph.GraphNode<String> e = graph.addNode("e");
            Graph.GraphNode<String> f = graph.addNode("f");
            Graph.GraphNode<String> g = graph.addNode("g");
            Graph.GraphNode<String> h = graph.addNode("h");

            graph.addEdge(a, b);
            graph.addEdge(a, f);
            graph.addEdge(b, c);
            graph.addEdge(b, f);
            graph.addEdge(c, d);
            graph.addEdge(d, b);
            graph.addEdge(e, f);
            graph.addEdge(f, c);
            graph.addEdge(g, h);



            System.out.println("Grafo iniziale");
            //System.out.println(graph.getNodes());
            System.out.println(graph);

            System.out.println("Rimozione " + f + "," + c);
            graph.removeEdge(f,c);
            System.out.println(graph);

            System.out.println("Rimozione " + c + "," + b);
            graph.removeEdge(c,b);
            System.out.println(graph);

            System.out.println("Rimozione " + c + "," + d);
            graph.removeEdge(c,d);
            System.out.println(graph);

            System.out.println("Aggiunta " + c + "," + f);
            graph.addEdge(c,f);
            System.out.println(graph);

            System.out.println("Aggiunta " + d + "," + c);
            graph.addEdge(d,c);
            System.out.println(graph);

            System.out.println("Rimozione nodo " + d);
            graph.removeNode(d);
            System.out.println(graph);

            System.out.println("Rimozione nodo " + f);
            graph.removeNode(f);
            System.out.println(graph);

            System.out.println("Rimozione nodo " + c);
            graph.removeNode(c);
            System.out.println(graph);
        }
        else if (argv[0].equals("sweep")) {
        	Graph<String> graph = new Graph<String>();

            Graph.GraphNode<String> a = graph.addNode("a");
            Graph.GraphNode<String> b = graph.addNode("b");
            Graph.GraphNode<String> c = graph.addNode("c");
            Graph.GraphNode<String> d = graph.addNode("d");
            Graph.GraphNode<String> e = graph.addNode("e");
            Graph.GraphNode<String> f = graph.addNode("f");
            Graph.GraphNode<String> g = graph.addNode("g");
            Graph.GraphNode<String> h = graph.addNode("h");

            graph.addEdge(a, b);
            graph.addEdge(a, f);
            graph.addEdge(b, c);
            graph.addEdge(b, f);
            graph.addEdge(c, d);
            graph.addEdge(d, b);
            graph.addEdge(e, f);
            graph.addEdge(f, c);
            graph.addEdge(g, h);
            
            System.out.println("Grafo:");
            System.out.println(graph);
            GraphServices.sweep(graph);
        }
        else if (argv[0].equals("top_sort")) {
        	Graph<String> graph = new Graph<String>();

            Graph.GraphNode<String> a = graph.addNode("a");
            Graph.GraphNode<String> b = graph.addNode("b");
            Graph.GraphNode<String> c = graph.addNode("c");
            Graph.GraphNode<String> d = graph.addNode("d");
            Graph.GraphNode<String> e = graph.addNode("e");
            Graph.GraphNode<String> f = graph.addNode("f");
            Graph.GraphNode<String> g = graph.addNode("g");
            Graph.GraphNode<String> h = graph.addNode("h");

            graph.addEdge(a, b);
            graph.addEdge(a, f);
            graph.addEdge(b, c);
            graph.addEdge(b, f);
            graph.addEdge(c, d);
            graph.addEdge(d, b);
            graph.addEdge(e, f);
            graph.addEdge(f, c);
            graph.addEdge(g, h);
            
            System.out.println("Grafo:");
            System.out.println(graph);
            
            System.out.println("Primo tentativo: (dovrebbe fallire)");
            GraphServices.topologicalSort(graph);
            
            System.out.println("Rimozione arco (d,b)");
            graph.removeEdge(d, b);
            
            System.out.println("Nuovo Grafo:");
            System.out.println(graph);
            
            System.out.println("Secondo tentativo: (dovrebbe riuscire)");
            GraphServices.topologicalSort(graph);
        }
        else if (argv[0].equals("strong_cc")) {
        	Graph<String> graph = new Graph<String>();

            Graph.GraphNode<String> a = graph.addNode("a");
            Graph.GraphNode<String> b = graph.addNode("b");
            Graph.GraphNode<String> c = graph.addNode("c");
            Graph.GraphNode<String> d = graph.addNode("d");
            Graph.GraphNode<String> e = graph.addNode("e");
            Graph.GraphNode<String> f = graph.addNode("f");
            Graph.GraphNode<String> g = graph.addNode("g");
            Graph.GraphNode<String> h = graph.addNode("h");

            graph.addEdge(a, b);
            graph.addEdge(a, f);
            graph.addEdge(b, c);
            graph.addEdge(b, f);
            graph.addEdge(c, d);
            graph.addEdge(d, b);
            graph.addEdge(e, f);
            graph.addEdge(f, c);
            graph.addEdge(g, h);
            
            System.out.println("Grafo 1:");
            System.out.println(graph);
            
            GraphServices.strongConnectedComponents(graph);
            System.out.println("\n");

            Graph<String> graph2 = new Graph<String>();

            Graph.GraphNode<String> a2 = graph2.addNode("a");
            Graph.GraphNode<String> b2 = graph2.addNode("b");
            Graph.GraphNode<String> c2 = graph2.addNode("c");
            Graph.GraphNode<String> d2 = graph2.addNode("d");
            Graph.GraphNode<String> e2 = graph2.addNode("e");

            graph2.addEdge(a2, b2);
            graph2.addEdge(b2, c2);
            graph2.addEdge(c2, a2);
            graph2.addEdge(a2, d2);
            graph2.addEdge(d2, e2);
            
            System.out.println("Grafo 2:");
            System.out.println(graph2);
            
            GraphServices.strongConnectedComponents(graph2);
            System.out.println("\n");

            Graph<String> graph3 = new Graph<String>();

            Graph.GraphNode<String> a3 = graph3.addNode("0");
            Graph.GraphNode<String> b3 = graph3.addNode("1");
            Graph.GraphNode<String> c3 = graph3.addNode("2");
            Graph.GraphNode<String> d3 = graph3.addNode("3");
            Graph.GraphNode<String> e3 = graph3.addNode("4");
            Graph.GraphNode<String> f3 = graph3.addNode("5");
            Graph.GraphNode<String> g3 = graph3.addNode("6");
            Graph.GraphNode<String> h3 = graph3.addNode("7");
            Graph.GraphNode<String> i3 = graph3.addNode("8");

            // 0-1-2-3
            graph3.addEdge(a3, b3);
            graph3.addEdge(b3, c3);
            graph3.addEdge(c3, d3);
            graph3.addEdge(d3, a3);

            graph3.addEdge(c3, e3);

            // 4-5-6
            graph3.addEdge(e3, f3);
            graph3.addEdge(f3, g3);
            graph3.addEdge(g3, e3);

            graph3.addEdge(h3, g3);
            graph3.addEdge(h3, i3);


            
            System.out.println("Grafo 3:");
            System.out.println(graph3);
            
            GraphServices.strongConnectedComponents(graph3);
            System.out.println("\n");
        }
        else if (argv[0].equals("esameGiugno2020A")) {
			Graph<Integer> graph = new Graph<Integer>();
			Graph.GraphNode<Integer> n5 = graph.addNode(5);
			Graph.GraphNode<Integer> n2 = graph.addNode(2);
			Graph.GraphNode<Integer> n11 = graph.addNode(11);
			Graph.GraphNode<Integer> n10 = graph.addNode(10);
			Graph.GraphNode<Integer> n9 = graph.addNode(9);
			Graph.GraphNode<Integer> n3 = graph.addNode(3);
			Graph.GraphNode<Integer> n7 = graph.addNode(7);
			Graph.GraphNode<Integer> n8 = graph.addNode(8);
			
			graph.addEdge(n5, n11);
			graph.addEdge(n11, n2);
			graph.addEdge(n11, n10);
			graph.addEdge(n11, n9);
			graph.addEdge(n7, n11);
			graph.addEdge(n7, n8);
			graph.addEdge(n3, n10);
			graph.addEdge(n3, n8);
			graph.addEdge(n8, n9);
			
			System.out.println("Grafo :");
            System.out.println(graph);
            
            System.out.println("connectedComponent con s = 11 e k = 5 :");
			GraphServices.connectedComponent(graph, n11, 5);
			System.out.println("connectedComponent con s = 7 e k = 5 :");
			GraphServices.connectedComponent(graph, n7, 5);

				
		}
		else if (argv[0].equals("esameGiugno2020B")) {
			Graph<Integer> graph = new Graph<Integer>();
			Graph.GraphNode<Integer> n5 = graph.addNode(5);
			Graph.GraphNode<Integer> n2 = graph.addNode(2);
			Graph.GraphNode<Integer> n11 = graph.addNode(11);
			Graph.GraphNode<Integer> n10 = graph.addNode(10);
			Graph.GraphNode<Integer> n9 = graph.addNode(9);
			Graph.GraphNode<Integer> n3 = graph.addNode(3);
			Graph.GraphNode<Integer> n7 = graph.addNode(7);
			Graph.GraphNode<Integer> n8 = graph.addNode(8);
			
			graph.addEdge(n5, n11);
			graph.addEdge(n11, n2);
			graph.addEdge(n11, n10);
			graph.addEdge(n11, n9);
			graph.addEdge(n7, n11);
			graph.addEdge(n7, n8);
			graph.addEdge(n3, n10);
			graph.addEdge(n3, n8);
			graph.addEdge(n8, n9);
			
			System.out.println("Grafo :");
            System.out.println(graph);
            
            System.out.println("viciniEntroK con K=1 :");
			LinkedList<Graph.GraphNode<Integer>> l1 = GraphServices.viciniEntroK(graph, n7, 1);
			for(Graph.GraphNode<Integer> n : l1){
				System.out.print(n.value + " ");
			}
			System.out.println();
			
			System.out.println("viciniEntroK con K=3 :");
			LinkedList<Graph.GraphNode<Integer>> l2 = GraphServices.viciniEntroK(graph, n7, 3);
			for(Graph.GraphNode<Integer> n : l2){
				System.out.print(n.value + " ");
			}
			System.out.println();

				
		}
    } //main
} // class
