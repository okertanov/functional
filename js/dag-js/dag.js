/**
    @brief IIFE
    @see https://developer.mozilla.org/en/JavaScript/Reference/Operators/function
*/
(function(){

    /**
        @brief Strict mode by default
        @see https://developer.mozilla.org/en/JavaScript/Strict_mode
    */
    "use strict";

    /**
        @class DagException
        @brief
    */
    function DagException(message) {
        this.message = message;
        this.name = "DagException";
    }

    /**
        @class Node
        @brief
    */
    function Node(payload, nodes) {
        var payload = payload || '<empty>';
        var nodes = nodes || [];

        return {
            payload: payload,
            nodes: nodes,
            add: function(node) {
                this.nodes.push(node);
                return this;
            },
            remove: function(node) {
                this.nodes.splice(this.nodes.indexOf(node), 1);
                return this;
            }
        };
    }

    /**
        @class Dag
        @brief
    */
    function Dag(param) {
        var nodes = [];

        if (param) {
            if (Array.isArray(param)) {
                nodes = param;
            }
            else if(typeof(param) == 'object') {
                nodes.push(param);
            }
            else {
                throw new DagException('Parameter error: param');
            }
        }

        return {
            nodes: nodes,
            add: function(node) {
                this.nodes.push(node);
                return this;
            },
            remove: function(node) {
                this.nodes.splice(this.nodes.indexOf(node), 1);
                return this;
            },
            contains: function(n) {
                return this.nodes.indexOf(n) != -1;
            },
            visitAll: function(visitor, predicate, nodes) {
                var nodes = nodes || this.nodes;
                this.visited = false;

                var self = this;
                nodes.forEach(function(n) {
                    if(predicate(n)) {
                        if (n.nodes && n.nodes.length > 0) {
                            self.visitAll(visitor, predicate, n.nodes);
                        }

                        self.visited = true;
                        return visitor(n);
                    }
                });

                return this.visited;
            },
            visitLeafs: function(visitor, predicate, nodes) {
                var nodes = nodes || this.nodes;
                this.visited = false;

                var self = this;
                nodes.forEach(function(n) {
                    if(predicate(n)) {
                        if (n.nodes && n.nodes.length > 0) {
                            self.visitLeafs(visitor, predicate, n.nodes);
                        }
                        else {
                            self.visited = true;
                            return visitor(n);
                        }
                    }
                });

                return this.visited;
            },
            visitSingle: function(visitor, predicate, nodes) {
                var nodes = nodes || this.nodes;
                this.visited = false;

                for (var i in nodes) {
                    if (nodes.hasOwnProperty(i)) {
                        var n = nodes[i];
                        if(predicate(n)) {
                            if (n.nodes && n.nodes.length > 0) {
                                this.visitSingle(visitor, predicate, n.nodes);
                                if(this.visited) {
                                    break;
                                }
                            }
                            else {
                                this.visited = true;
                                visitor(n);
                                return false;
                            }
                        }
                    }
                }

                return this.visited;
            },
            makeEmpty: function() {
                return new Dag();
            }
        };
    }

    /**
        @fn main
        @brief
    */
    function main() {
        console.log('Starting DAG...');

        var testNodes = [
            new Node('1').add(new Node('1.1')).add(new Node('1.2')).add(new Node('1.3')),
            new Node('2'),
            new Node('3'),
            new Node('4').add(new Node('4.1')).add(new Node('4.2')),
            new Node('5')
        ];

        var rootNode = new Node('rootNode', testNodes);
        var dag = new Dag(rootNode);

        var visitor = function(n) {
            console.log(n.payload);
        };

        var predicate = function(n) {
            return true;
        };

        console.log('------------------------------------');
        var v1 = dag.visitAll(visitor, predicate);
        console.log('Visited:', v1);

        console.log('------------------------------------');
        var v2 = dag.visitLeafs(visitor, predicate);
        console.log('Visited:', v2);

        console.log('------------------------------------');
        var v3 = dag.visitSingle(visitor, predicate);
        console.log('Visited:', v3);

        console.log('------------------------------------');
        var dagEmpty = new Dag([]);
        var v4 = dagEmpty.visitAll(visitor, predicate);
        console.log('Visited:', v4);
        var v5 = dagEmpty.visitLeafs(visitor, predicate);
        console.log('Visited:', v5);
        var v6 = dagEmpty.visitSingle(visitor, predicate);
        console.log('Visited:', v6);

        console.log('------------------------------------');
        var visitOnceDag = new Dag(rootNode);
        var visitOnceProcessed = visitOnceDag.makeEmpty();

        var onceVisitor = function(n) {
            console.log('\t', n.payload);
            visitOnceProcessed.add(n);
        };

        var oncePredicate = function(n) {
            return !visitOnceProcessed.contains(n);
        };

        var iteration = 0;
        while(visitOnceDag.visitSingle(onceVisitor, oncePredicate)) {
            console.log('\t', 'In iteration:', ++iteration);
        }

        console.log('Done. Bye!');
    }


    /**
        @brief Launch test code
    */
    main();

})();
