#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>


SDL_Texture* tex_img_png(char * s, SDL_Renderer* renderer){

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
    return image_btn_tex;
}

int main(int argc, char** argv)
{
	int x,y,i;
	int pos = 1;
    //Le pointeur vers la fenetre
	SDL_Window* pWindow = NULL;
	//Le pointeur vers la surface incluse dans la fenetre
    SDL_Surface *image = NULL;
	SDL_Surface *image_hover = NULL;
	SDL_Surface *option1 = NULL;
	SDL_Surface *option2 = NULL;
	SDL_Surface *option3 = NULL;
	SDL_Surface *titre1 = NULL;
	SDL_Surface *titre2 = NULL;
	SDL_Surface *titre3 = NULL;
	SDL_Renderer *renderer=NULL;
	SDL_Rect imgBtnRect;


	SDL_Rect titre1DestRect;
	SDL_Rect titre2DestRect;
	SDL_Rect titre3DestRect;

	SDL_Rect opt1DestRect;	
	SDL_Rect opt2DestRect;
	SDL_Rect opt3DestRect;



	// Le pointeur vers les polices
	TTF_Font *police = NULL;
	TTF_Font *police2 = NULL;
	TTF_Font *police3 = NULL;
	// Une variable de couleur noire
	SDL_Color white = {255, 255, 255};

    /* Initialisation simple */
    if (SDL_Init(SDL_INIT_VIDEO) != 0 ) {
        fprintf(stdout,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
        return -1;
    } 

	/* Initialisation TTF */
	if(TTF_Init() == -1) {
		fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
		exit(EXIT_FAILURE);
	}


	/* Création de la fenêtre */
	pWindow = SDL_CreateWindow("The Biding of Isaac REMASTERED",SDL_WINDOWPOS_UNDEFINED, 
																SDL_WINDOWPOS_UNDEFINED,
												 				1080,
												  				650,
												  				SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE);

	if(!pWindow){SDL_Texture* tex_img_png(char * s, SDL_Renderer* renderer);
		fprintf(stderr, "Erreur à la création de la fenetre : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}


	renderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);
	if(renderer == NULL){
		fprintf(stderr, "Erreur à la création du renderer\n");
		exit(EXIT_FAILURE);
	}

	if( (police = TTF_OpenFont("Dancing Days.ttf", 15)) == NULL || (police2 = TTF_OpenFont("upheavtt.ttf", 30)) == NULL || (police3 = TTF_OpenFont("upheavtt.ttf", 150)) == NULL){
		fprintf(stderr, "erreur chargement font\n");
		exit(EXIT_FAILURE);
	}

	option1 = TTF_RenderUTF8_Blended(police, "JOUER", white);
	option2 = TTF_RenderUTF8_Blended(police, "CREDITS", white);
	option3 = TTF_RenderUTF8_Blended(police, "QUITTER", white);
	if(!option1 || !option2 || !option3 ){
		fprintf(stderr, "Erreur à la création des options : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	
	SDL_Texture *option1_tex = SDL_CreateTextureFromSurface(renderer, option1);
	SDL_Texture *option2_tex = SDL_CreateTextureFromSurface(renderer, option2); 
	SDL_Texture *option3_tex = SDL_CreateTextureFromSurface(renderer, option3); 
	if(!option1_tex || !option2_tex || !option3_tex){
		fprintf(stderr, "Erreur à la création des rendus des option : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}


	titre1 = TTF_RenderUTF8_Blended(police2, "the binding of", white);
	titre2 = TTF_RenderUTF8_Blended(police3, "ISAAC", white);
	titre3 = TTF_RenderUTF8_Blended(police2, "REMASTERED", white);
	if(!titre1 || !titre2 || !titre3 ){
		fprintf(stderr, "Erreur à la création des textes : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	
	SDL_Texture *titre1_tex = SDL_CreateTextureFromSurface(renderer, titre1);
	SDL_Texture *titre2_tex = SDL_CreateTextureFromSurface(renderer, titre2); 
	SDL_Texture *titre3_tex = SDL_CreateTextureFromSurface(renderer, titre3); 
	if(!titre1_tex || !titre2_tex || !titre3_tex){
		fprintf(stderr, "Erreur à la création des rendus des textes : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	/* on a la texture, plus besoin du texte */
	SDL_FreeSurface(option1); 
	SDL_FreeSurface(option2);
	SDL_FreeSurface(option3);
	SDL_FreeSurface(titre1); 
	SDL_FreeSurface(titre2);
	SDL_FreeSurface(titre3);

	/* Positionnement des titres */
	titre1DestRect.x = 400;
	titre1DestRect.y = 15;

	titre2DestRect.x = 300;
	titre2DestRect.y = 10;

	titre3DestRect.x = 430;
	titre3DestRect.y = 130;


	/* Positionnement des textes dans les boutons */
    opt1DestRect.x = 477;
	opt1DestRect.y = 207;

	opt2DestRect.x = 470;
	opt2DestRect.y = 297;

	opt3DestRect.x = 465;
	opt3DestRect.y = 388;

	SDL_QueryTexture(option1_tex, NULL, NULL, &(opt1DestRect.w), &(opt1DestRect.h));
	SDL_QueryTexture(option2_tex, NULL, NULL, &(opt2DestRect.w), &(opt2DestRect.h));
	SDL_QueryTexture(option3_tex, NULL, NULL, &(opt3DestRect.w), &(opt3DestRect.h));

	SDL_QueryTexture(titre1_tex, NULL, NULL, &(titre1DestRect.w), &(titre1DestRect.h));
	SDL_QueryTexture(titre2_tex, NULL, NULL, &(titre2DestRect.w), &(titre2DestRect.h));
	SDL_QueryTexture(titre3_tex, NULL, NULL, &(titre3DestRect.w), &(titre3DestRect.h));


	//Chargement de l'image bouton
    SDL_Texture *image_btn_tex = tex_img_png("btn.png",renderer);
    //Chargement de l'image bouton (utilisé quand la souris passe sur l'image)
	SDL_Texture *image_btnHover_tex = tex_img_png("btnHover.png",renderer);

	SDL_Texture *temp;

	SDL_FreeSurface(image);
	SDL_FreeSurface(image_hover);
	
	if( pWindow )
	{
		int running = 1; 
		while(running) { 
			SDL_Event e;
			while(SDL_PollEvent(&e)) { 
				switch(e.type) { 
					case SDL_QUIT: running = 0; break;
					case SDL_KEYDOWN:
					switch(e.key.keysym.sym){
					    case SDLK_ESCAPE: running = 0; break;
				    	case SDLK_DOWN:
						if(pos < 3 ){
							pos++;
						}
						else{
							pos=1;
						}break;
						case SDLK_UP:
							if(pos > 1){
								pos--;
							}
							else{
								pos=3;
							}
						break;
						case SDLK_RETURN:
							switch(pos){
								case 1:
								/*lancement du jeu*/
								break;
								case 2:
								/*credit*/
								break;
								case 3:
									running=0;
									break;
							}
						break;
					}
					case SDL_WINDOWEVENT:      
						SDL_RenderClear(renderer);                  
                        SDL_QueryTexture(image_btnHover_tex, NULL, NULL, &(imgBtnRect.w), &(imgBtnRect.h));
						//Positionnement du premier bouton
                        imgBtnRect.x = 440;
                        imgBtnRect.y = 180;
						if( pos == 1 ){
							temp = image_btnHover_tex;
						}
						else{
							temp = image_btn_tex;
						}
						SDL_RenderCopy(renderer,temp,NULL,&imgBtnRect);

						imgBtnRect.x=440;
						imgBtnRect.y=270;
						if( pos == 2 ){
							temp = image_btnHover_tex;
						}
						else{
							temp = image_btn_tex;
						}
						SDL_RenderCopy(renderer,temp,NULL,&imgBtnRect);

						imgBtnRect.x=440;
						imgBtnRect.y=360;
						if( pos == 3 ){
							temp = image_btnHover_tex;
						}
						else{
							temp = image_btn_tex;
						}
						SDL_RenderCopy(renderer,temp,NULL,&imgBtnRect);

						/* Affichage texte sur boutons */
						SDL_RenderCopy(renderer, option1_tex, NULL, &opt1DestRect);
						SDL_RenderCopy(renderer, option2_tex, NULL, &opt2DestRect);
						SDL_RenderCopy(renderer, option3_tex, NULL, &opt3DestRect);

						/* Affichage des titres */
						SDL_RenderCopy(renderer, titre1_tex, NULL, &titre1DestRect);
						SDL_RenderCopy(renderer, titre2_tex, NULL, &titre2DestRect);
						SDL_RenderCopy(renderer, titre3_tex, NULL, &titre3DestRect);

                        /* On fait le rendu ! */
                        SDL_RenderPresent(renderer);


					break;
				} 
			} 
		}
	} else {
		fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
	}

	//Destruction de la fenetre
	SDL_DestroyWindow(pWindow);

	TTF_CloseFont(police); /* Doit être avant TTF_Quit() */
	TTF_Quit();
    SDL_Quit();

    return 0;
}


