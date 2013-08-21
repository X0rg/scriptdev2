/***************************************************
  World mob, Pics Foudroyés, Brunnhildar
  ==================
AUTEUR: Xorg
DATE: 06/11/2012
CORRECTIF: Modification de la faction de la créature 30174 en aggressive.

COMMENTAIRES:

30174 : Ours de guerre du Hyldsmeet
****************************************************/

REPLACE INTO 'creature_template' SET 'faction_A'='16' WHERE ('entry'='30174');
REPLACE INTO 'creature_template' SET 'faction_H'='16' WHERE ('entry'='30174');