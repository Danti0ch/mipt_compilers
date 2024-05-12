eval -> expressions + iterative
do not implement what cannot be used

<program> := <func>

<func> := <simple func>

<simple func> := fn main body: <body>

<body> := { <statement>* }

<statement> := <local_statement> |
               let <ident> -> int;

<local_statement> := form <expr>; | 
               <ident> <- <expr>; |
               print expr; |
               if (<bool expr>) {
                    <local_body>
               } |
               if (<bool expr>) {
                    <local_body>
               } else {
                    <local_body>
               } |
               loop (<bool expr>) {
                    <local_body>
               }

<local_body> := <local_statement>*

<bool expr> := <expr> [and|or|<|<=|>|>=|eq|neq] <expr>
<expr> :=  <ident> |
           <constant> |
           <bool expr> |
           <arithm expr> |
           ( <expr> )

<arithm expr> := <expr> [+|-|*|/|%] <expr>

<ident> := [a-zA-Z][a-zA-Z0-9]*
<constant> := [0-9]+
