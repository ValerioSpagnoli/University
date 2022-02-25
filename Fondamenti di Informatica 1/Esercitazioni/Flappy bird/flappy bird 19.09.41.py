import pygame
import random

pygame.init()

sfondo = pygame.image.load('Immagini/sfondo.png')
uccello = pygame.image.load('Immagini/uccello.png')
base = pygame.image.load('Immagini/base.png')
gameover = pygame.image.load('Immagini/gameover.png')
tubo_giu = pygame.image.load('Immagini/tubo.png')
tubo_su = pygame.transform.flip(tubo_giu, False, True)

schermo = pygame.display.set_mode((288,512))
FPS = 50

def disegna_oggetti():
    schermo.blit(sfondo, (0,0))
    schermo.blit(uccello, (uccellox, uccelloy))

def aggiorna():
    pygame.display.update()
    pygame.time.Clock().tick(FPS)
    
def inizializza():
    global uccellox, uccelloy, uccello_vely
    uccellox, uccelloy = 60, 150
    uccello_vely = 0

inizializza()

while True:
    uccello_vely += 1
    uccelloy += uccello_vely
    disegna_oggetti()
    aggiorna()






