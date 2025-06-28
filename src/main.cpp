#include <cstdio>

#include "core/window.hpp"
#include "editor/editor_ui.hpp"
#include "loading/model_loader.hpp"


int main() 
{
    Window window(800, 600, "COUCOU");
    EditorUI ui(window, "#version 330 core");

    while (!window.ShouldClose())
    {
        ui.Render();
        
        window.PostRender();
    }

    return 0;
}

/*

Bonjour Eva,


J'espère que tu lis bien cette lettre lors du jour de ton anniversaire et non avant :(
Je suis désolé de pas pouvoir y être présent. Je comprends que tu sois mal et c'est entièrement de ma faute. C'est vraiment horrible pour moi de ne pas pouvoir être la à ce moment auquel tu tiens tant et je regrette profondément de partir aussi tôt.
Comme tu le sais, ces dernières semaines, voire ces derniers mois n'ont pas été les plus simples, que ça soit pour toi ou pour moi. Mais je crois en toi, en nous, pour pouvoir en ressortir, non sans égratinures, mais avec un amour qui dure toujours. 
Je croise les doigts pour que les cadeaux que je t'ai achetés te plaisent et qu'ils correspondent à ce que tu attendais de ma part.
Je pense que voir ta meilleure amie te fera du bien et que tu pourras passer le plus de temps avec elle pour profiter du fait qu'elle soit en France. Mais c'est pas une raison pour oublier que j'existe hein !! Et pense à moi quand tu es avec elle :)


Tu es la fille la plus merveilleuse que j'ai jamais rencontrée. Ton sourire, ton rire, ton caractère, ton humour ou tes mains, je trouve tout chez toi incroyable, ce qui te rends si spéciale à mes yeux. Je sais que je me répète souvent dans mes lettres, mais je trouve que je te le dis pas assez souvent, et que sincèrement, je devrais le faire tout les matins pour exprimer à quel point ce que je pense est vrai. A vrai dire, juste penser à toi pour écrire cette lettre me fait sourire.


Cette année avec toi été remplie de bonheur. Tout les moments où on s'est moqués de Chloé et Maxime, ou on a rigolé sur les trucs les plus stupides pendant des minutes entières, toutes mes blagues de merde qui te font rigoler que parce que je rigole seul. Quand tu es venue chez moi pour prendre soin de moi alors que j'était malade, deux fois, et que je me sentais directement mieux quand j'étais dans tes bras. Aussi toutes les fois ou on est allés à Auchan pour toujours acheter les mêmes choses, et ou ma caisse ne marchait jamais. J'ai beaucoup trop de moments de pure joie en tête pour tous les citer dans cette lettre, et je te remercie toi, et que toi pour cela. 


For the love of my life,
Victor

She'll never read this beacause she's leaving me before her birthday. I don't even think I'm going to be able to give her my gifts.                             

*/

