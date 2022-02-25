#pragma once

typedef int TipoInfoAlbero;

struct TipoNodoAlbero { 
  TipoInfoAlbero info; 
  TipoNodoAlbero *sinistro, *destro; 
};

void scambiaPuntatori(TipoNodoAlbero* nodo);

