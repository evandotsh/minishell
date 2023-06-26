### ⭐ Parser

>- Si les quote **" " ou ' '** ne sont pas fermé alors **return une erreur sytax**.
>
> - Si les caractère spéciaux tels que **"\\" ou ";" return une erreur sytax**.
>
> - Gérer **' '** qui doit empêcher le shell d’interpréter ***les méta-caractères***
présents dans la séquence entre guillemets.
>
> - Gérer **" "** qui doit empêcher le shell d’interpréter ***les méta-caractères***
présents dans la séquence entre guillemets **sauf le $**.
>
> - Gérer les pipes **|** en dehors des **Quotes**.
#
### ⭐ Lexer

> - Séparer les éléments avec les **"  *espace* "** pour avoir toutes les instruction.

> > <span style="color:yellow">Exemple: ls | wc -l</span> Ici nous avons 4 élément 
 > > - <span style="color:red">1:</span><span style="color:blue"> ls</span>
 > > - <span style="color:red">1:</span><span style="color:blue"> |</span>
 > > - <span style="color:red">1:</span><span style="color:blue"> wc</span>
  > > - <span style="color:red">1:</span><span style="color:blue"> -l</span>

> - Séparer les élément lors qu'ils sont collé aux **|** , **>**, **<**, **>>**, **<<**.

> > <span style="color:yellow">Exemple: ls|wc -l</span> Ici nous avons 4 élément mais il faut les séparer aux niveau des ***pipes***.
 > > - <font style="color:red">1:</font><font style="color:blue"> ls</font>
 > > - <span style="color:red">1:</span><span style="color:blue"> |</span>
 > > - <span style="color:red">1:</span><span style="color:blue"> wc</span>
  > > - <span style="color:red">1:</span><span style="color:blue"> -l</span>
#