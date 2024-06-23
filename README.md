// Trabalho 2 - Trees
// AED1 - Prof. José Augusto Baranauskas
// Alexandre Santato    | 14555162
// Leonardo Rizzo Costa | 14756204

Para o número de comparações na inserção nas AVL e ABB, foi considerada a implementação de árvore sem "count" que aceita repetição
Isto é, se um elemento x < p->entry resultar false, não é comparado se x > p->entry (o elemento já é adicionado na subárvore direita)
Ou seja, se não for menor, não há verificação se é maior, e o elemento vai direto para p->rightNode.
O professor comentou em sala de aula que esta implementação era válida e consistente com repetições (o elemento seria adicionado à direita)
Por este motivo, o número de comparações nas inserções pode variar das implementações que se basearam exclusivamente nos slides do professor.
O monitor (sim, você mesmo que está corrigindo) foi avisado pelo WhatsApp dessa mudança na implementação.