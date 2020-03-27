/*---------------------------------------------------------------------------------
*	Fichier	: Exercice 4 : TP5
*	Description	:
*
*
*  Horloges: ACLK = aucun, MCLK = SMCLK = DCO (1.048576 MHz)
*
*                MSP430G2553
*             -----------------
*         /|\|              XIN|-
*          | |                 |
*          --|RST          XOUT|-
*            |             |
*            |     P4.4/UCA1TXD|------------>
*            |                 | 9600 - 8N1
*            |     P4.5/UCA1RXD|<------------
*			 |			   P1.0|------> LED1
*			 |			   P4.7|------> LED2
*---------------------------------------------------------------------------------
* 	Polytech-Sorbonne : EI-2I-2 :
*	DARGA Arouna (arouna.darga@sorbonne-universite.fr)
* 	Version 0.1 (Tester avec code composer Version: 6.2)
*---------------------------------------------------------------------------------*/

/* Includes ----------------------------------------------------------------------*/
#include <msp430.h>  		/* inclusion du fichier  definition registre   */


/* Private typedef ---------------------------------------------------------------*/
/* Private define ----------------------------------------------------------------*/


/* Private macro -----------------------------------------------------------------*/
/* Private variables -------------------------------------------------------------*/
volatile unsigned char Caractere_Recu;



/* Private function prototypes ---------------------------------------------------*/
void InitUart_InterruptionRx(void);
void InitLEDsLaunchpad (void);




/*----------------------------------------------------------------------------
  Main Program
  @brief  Main program.: Point entree indispensable en C
  @param  None
  @retval None
 *----------------------------------------------------------------------------*/
int main()
	{

	  WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer
	  InitLEDsLaunchpad();
	  InitUart_InterruptionRx();

	  // Demasquage de la source d'interruption de P1.3
	  // ecrire le code a la ligne ci-dessous



	  while (1) //Boucle infinie
	  {
	  		// tout est realiser dans la routine interruption de USCI_A1



	  }
  }


/*----------------------------------------------------------------------------
  __interrupt void USCI_A1_ISR(void):  Routine interruption de USCI_A1
  @brief  : Routine appeler a chaque fois que :
  				1. un caractere est recu
  				2. un caractere est transmis 
  				dans ce exercice l'interruption de la transmission n'est pas activer)
  @param  aucun
  @retval aucun
 *----------------------------------------------------------------------------*/

#pragma vector=USCI_A1_VECTOR
__interrupt void USCI_A1_ISR(void)
{
	if (/* verifier que le drapeau de demande interruption de reception est a '1': bit b0 de UCA1IFG */)
	{
		/* si le bit bit b0 de UCA1IFG est a '1' alors un caractere est recu */

		// faire un reset du drapeau de demande interruption de reception est a '1': bit b0 de UCA1IFG 
		// ecrire le code a la ligne ci-dessous
		

		// Lire le caractere recu 
		// ecrire le code a la ligne ci-dessous

		// traiter le caractere : incrementer 
		// ecrire le code a la ligne ci-dessous

		
		// attendre que le buffer de transmission soit vide
		// transmettre le caractere traiter au PC
		// ecrire le code a la ligne ci-dessous

		
	}

}


/*----------------------------------------------------------------------------
  InitUartAvecInterruptionRx (void):  Initialisation de l'UART a  9600 Bauds
  @brief  : Initialise UART (voir ch.8 p. 474 de msp430x2xxxFamilyGuide.pdf)
  @param  aucun
  @retval aucun
 *----------------------------------------------------------------------------*/
void InitUart_InterruptionRx(void)
	{
	// 1. Configurer les pattes pour la liaison
	 // MSP430F5529 : // P4.5 = RXD, P4.4=TXD
	// mettre a '1' les bits b4 et b5 du registre P4SEL
	 // ecrire le code a la ligne ci-dessous
	P4SEL |=((1<<5)|(1<<4));

	//2. Choix horloge et configuration de la frequence pour le module USCIA0
		// Nous preons SMCLK configurer pour 1MHz Calibre: bits b7b6 du->"11"

		// mettre a '1' les bits b7 et b6 du registre UCA1CTL1
		// ecrire le code a la ligne ci-dessous
	UCA1CTL1 |=((1<<7)|(1<<6));


	// 3. Faire un reset (activer) de la state machine du USCI_A1
		// registre : UCAxCTL1, USCI_Ax Control Register 1
		// bit b0 (UCSWRST)  Software reset enable
		// 0 Disabled. USCI reset released for operation.
		// 1 Enabled. USCI logic held in reset state.

		// mettre a '1' le bits b0 du registre UCA1CTL1
		// ecrire le code a la ligne ci-dessous
	UCA1CTL1|=((1<<0));


	// 4. choix du mode asynchrone UART
	// 4.1 Choix asynchrone : bit b0 de UCAxCTL0 -> '0'
		// mettre a '0' le bits b0 du registre UCA1CTL0
		// ecrire le code a la ligne ci-dessous
	UCA1CTL0 &= ~(1<<0);

	// 4.2 choix mode UART : bits b2b1 de UCA1CTL0 ->"00"

		// mettre a '0' les bits b2 et b1 du registre UCA1CTL0
		// ecrire le code a la ligne ci-dessous
	UCA1CTL0 &= ~((1<<2)|(1<<1));
	// 5.1 Choix nombre de bits STOP: Ici 1 BIT STOP: bit b3(UCSPB) de UCA1CTL0 ->'0'

		// mettre a '0' le bits b3 du registre UCA1CTL0
		// ecrire le code a la ligne ci-dessous
	UCA1CTL0 &= ~(1<<3);
	//	5.2 Choix taille du format de donnees des caracteres: Caractere coder 8bits
		// bit b4 de UCA0CTL0->'0'

		// mettre a '0' le bits b4 du registre UCA1CTL0
		// ecrire le code a la ligne ci-dessous

	UCA1CTL0 &= ~(1<<4);

	// 5.3. Choix bit de parite ou pas : Pas de bit de parite : bit b7(UCPEN) ->'0'

		// mettre a '0' le bits b7 du registre UCA1CTL0
		// ecrire le code a la ligne ci-dessous
	UCA1CTL0 &= ~(1<<7);

	// 5.4. Choix sens de tranfert des bit: LSB en premier: Bitb5 (UCMSB)de UCA1CTL0 ->'0'

		// mettre a '0' le bits b5 du registre UCA1CTL0
		// ecrire le code a la ligne ci-dessous
	UCA1CTL0 &= ~(1<<5);
	// 6. Configurer la vitesse de transfert : 9600
		// la formule de la valeur a ecrire pour choisir le baudrate est : Frequence/BaudRate
		// Frequence= 1048576
		// Baudrate = 9600 = 109.22 =109=0x6D
		// calculer la valeur a ecrire et convertir le resultat en hexadecimal puis ecrire
		// 1. octet de poids faible dans le registre UCA1BR0
		// 2. octet de poids fort dans le registre UCA1BR1

		// ecrire le code a la ligne ci-dessous
	 UCA1BR0 = 0x6D;
	 UCA1BR1 = 0x00;

	// 7. Relacher le Reset (Deactiver) de la machine a etat du USCI_A1
		// bit b0 (UCSWRST) de UCA1CTL1 -> '0'
		// mettre a '0' le bits b0 du registre UCA1CTL1
		// ecrire le code a la ligne ci-dessous
	 UCA1CTL1 &= ~(1<<0);

    // 8. Configuration de la demande Interruption.
    // On ne souhaite pas interruption :

	 // mettre le bit b0 du registre UCA1IE à '1'
	 // ecrire le code a la ligne ci-dessous

	}

/*----------------------------------------------------------------------------
  InitLEDsLaunchpad:  Configuration et Initialisation (LED1->P1.0, LED2->P1.6)
  @brief  :
  @param  aucun
  @retval aucun
 *----------------------------------------------------------------------------*/
void InitLEDsLaunchpad (void) {
	P1DIR |= (1<<0); // Led rouge en sortie
	P3DIR |= (1<<7); // Led verte en sortie
	P1OUT &= ~(1<<0); // eteinte
	P1OUT &= ~(1<<7); // eteinte
}


