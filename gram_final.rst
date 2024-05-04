eval -> expressions + iterative
do not implement what cannot be used

<program> := <func>*

<func> := <simple func> | <chrom>

<simple func> := fn <ident> <arg> <argsec> body: <body> |
                fn <ident> <arg> body: <body> | 

<chrom> := chrom <ident> <arg> <argsec> mutation: <float> generations: [0-9]+ <chrom_body>

<chrom_body> := <chrom_body_data> | <chrom_body_res>
<chrom_body_data> := edata: [<expr>, <expr>]+
<chrom_body_res> := eres: <body>

<arg> := -> <type> <body> | -> <type>

<body> := { <statement>* }

<argsec> := args: [<argsec_body_item>,]* <argsec_body_item>
<argsec_body_item> := <ident> <arg>

<type> := <simple_type>

<simple_type> := int

<statement> := form <expr>; |
               let <ident> <arg>; |
               <ident> <- <expr>; |
               print ( expr ); |
               <func call>; |
               if (<bool expr>) {
                    <statement>*
               } |
               if (<bool expr>) {
                    <statement>*
               } else {
                    <statement>*
               } |
               loop (<bool expr>) {
                    <statement>*
               }

<func call> := <ident>(<expr>*)

<bool expr> := <expr> [and|or|<|<=|>|>=|eq|neq] <expr>
<expr> := <bool expr> |
           ( <expr> ) |
           <arithm expr> |
           [0-9]+ |
           <func call> |
           <ident>

<arithm expr> := <expr> [+|-|*|/|%] <expr>

<gen> := gen <ident> <arg> <argsec> <body>

