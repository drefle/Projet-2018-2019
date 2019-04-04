#include "tout.h"

extern
SDL_Texture* tex_img_png(char * s, SDL_Renderer *renderer){

    SDL_RWops *rwop=SDL_RWFromFile(s, "rb");
	SDL_Surface *image=IMG_LoadPNG_RW(rwop);
	if(!image) {
	     printf("IMG_LoadPNG_RW: %s\n", IMG_GetError());
	}
	SDL_Texture *image_btn_tex = SDL_CreateTextureFromSurface(renderer, image);
	if(!image_btn_tex){
		fprintf(stderr, "Erreur à la création du rendu de l'image : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	SDL_FreeSurface(image); /* on a la texture, plus besoin de l'image */
  if(image_btn_tex!= NULL){
    return image_btn_tex;
  }
  else{
    return 0;
  }
}

extern
void init_res(t_res *ressource, SDL_Renderer *salle_render){
  ressource->obstacle_tex=tex_img_png("obstacle.png",salle_render);
  ressource->case_vide_tex = tex_img_png("case_vide.png",salle_render);
  ressource->perso_tex = tex_img_png("perso.png",salle_render);
  ressource->porte_tex = tex_img_png("porte.png",salle_render);
  ressource->monstre_tex = tex_img_png("monstre.png",salle_render);
  ressource->projectile_tex = tex_img_png("projectile.png",salle_render);
  fprintf(stderr,"ok init res");
}
