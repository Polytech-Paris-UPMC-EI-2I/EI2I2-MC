/*---------------------------------------------------------------------------------
*	Fichier	: Exercice 1 : TP5
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
unsigned char Caractere_Recu;



/* Private function prototypes ---------------------------------------------------*/
void InitUart_SansInterruption(void);
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
	  InitUart_SansInterruption();


	  while (1) //Boucle infinie
	  {
        /* Attente que le registre de reception soit rempli par le code du caractere recu
	      scrutation du bit b0 (UCRXIFG) du registre UCAxIFG (USCI_Ax Interrupt Flag Register)
	      si ce bit passe a '1' c'est que le caractere est recu
	    */
	    while (/* ecrire le code */ )
	    {
	      /* on reste dans cette boucle tant que le caracterse n'est pas arrivee
	        tant que bit b0 (UCA0RXIFG) vaut '0'
	      */
	    }
	    /* Arriver ici signifie que le bit b0 (UCRXIFG) du registre UCAxIFG vaut '1' : donc on peux lire un autre caractere */

	      /* Lecture du caractere depuis le registre UCA0RXBUF
	          et sauvegarde du caractere recu	dans la variable Caractere_Recu
	      */

	    // ecrire le code a la ligne ci-dessous
	   

          /* Traitement:
	         On incremente la valeur du caractere recu 
	       */
        // ecrire le code a la ligne ci-dessous


	   /* Pour la transmission
		 Attente que le registre de transmission de l'UART soit vide
          scrutation du bit b1 (UCTXIFG) du registre UCAxIFG (USCI_Ax Interrupt Flag Register)
	     si ce bit passe a '1' c'est que le caractere est trannsmis
	      et le registre de transmission est vide
	    */

	  while(/* ecrire le code */)
       {
		  /* tant que le bit b1 (UCTXIFG) du registre UCAxIFG  est a  '0' on attend ici!  */
       }

	   /* Arrivee ici signifie que bit b1 (UCTXIFG) du registre UCAxIFG vaut '1' : donc on peux envoyer un autre caractere */

	   // ecriture du caractere dans le registre de transmission
	   // ecrire le code a la ligne ci-dessous

	  }
  }



/*----------------------------------------------------------------------------
  InitUartAvecInterruptionRx (void):  Initialisation de l'UART a  9600 Bauds
  @brief  : Initialise UART (voir ch.8 p. 474 de msp430x2xxxFamilyGuide.pdf)
  @param  aucun
  @retval aucun
 *----------------------------------------------------------------------------*/
void InitUart_SansInterruption(void)
	{
/*----- Commentaires et explications fonctionnement UART--------
	Communication entre composants ou systeme electrique.
		- liaison de communication serie -> Tranfert information: BIT par BIT.
		  en theorie UN seul fil electrique suffit: Si information de 16 bits
		  il faut 16 transferts.
		  Inconvenient: Vitesse
		  Avantages: Cout et facile de mise en oeuvre
		- Liaison parallele-> Transfert information par groupe de BIT
		  en theorie il faut UN fil electrique par BIT: Si 16 bits -> 16 fils
		  transfert des 16 bits en un seul Transfert.
		  Inconvenient : Couts-> nombre de fils
		  Avantages : Vitesse
	liaison de communication serie:
		Il existe principalement 2 types:
		- Synchrone : En plus du fil (BIT a transferer) de donnees Il faut ajouter un fil
		  pour horloge. Ex. USB, SPI et I2C
		- Asychrone : Les 2 composants ou systeme s'accordent sur:
			1. la vitesse de transmission de donnees : Bauderate : Nombre de bits/seconde
			2. Le format des donnees :
				- 1 BIT qui indique le debut du transfert: START BIT -->'1'
				- Taille du Mot a transferer : 7 ou 8 BIT de donnees: Data : Nous prenons 8 bits
				- 1 ou 2 BIT de FIN du transfert : STOP BIT: Nous prenons 1 SEUL BIT STOP
			UART = Universal Asynchronous Receiver Transmitter

	Dans le MSP430 Les communications series sont gerer par 2 Peripheriques ou modules HARDWARE
	The universal serial communication interface (USCI) modules:
		1. USCI_Ax (x -> possible de trouver plusieurs modules): Gere UART, SPI et autres choses
		2. USCI_Bx : Gere I2C et SPI
		Dans le MSP430F5529 il y a 2 de chaque : USCI_A0, USCI_A1, USCI_B0 et USCI_B1
	Comme tout les peripheriques,il faut configurer avant utilisation:
	Les etapes suivantes sont a realisees:

	1. Configurer les pattes pour la liaison
		il 2 pattes :
		Rx -> Patte de reception de donnees venant de l'autre composant (PC ou Carte)
		Tx -> Patte de transmission dedonnees vers de l'autre composant (PC ou Carte)
		Registre : PxSEL
		Pour MSP430F5529 --> patte P4.4 et P4.5 -> P4SEL : bit b4 et b5
	2. Choix horloge et configuration de la frequence pour le module USCIA0
		registre: UCAxCTL1, USCI_Ax Control Register 1
		bit b7b6 (UCSSELx) USCI clock source select. These bits select the BRCLK source clock.
			"00" UCLK
			"01" ACLK
			"10" SMCLK
			"11" SMCLK

	3. Faire un reset (Activer) de la state machine du USCI_A1
		registre : UCAxCTL1, USCI_Ax Control Register 1
		bit b0 (UCSWRST)  Software reset enable
			'0' Disabled. USCI reset released for operation.
			'1' Enabled. USCI logic held in reset state.

	4. choix du mode asynchrone UART:
		4.1 : Choix asynchrone
				registre UCAxCTL0, USCI_Ax Control Register 0
				Bit b0(UCSYNC) Synchronous mode enable
					'0' Asynchronous mode : valeur par defaut
					'1' Synchronous mode
		4.2 choix mode UART
			registre UCAxCTL0 USCI_Ax Control Register 0
			bit b2b1 (UCMODEx)
			"00" UART mode
			"01" Idle-line multiprocessor mode
			"10" Address-bit multiprocessor mode
			"11" UART mode with automatic baud rate detection
	5. Configuration du format de donnees
		5.1 Choix nombre de bits STOP: Ici 1 BIT STOP
			registre : UCAxCTL0, USCI_Ax Control Register 0
			Bit b3(UCSPB) Stop bit select. Number of stop bits.
			'0' One stop bit : Valeur par defaut
			'1' Two stop bits
		5.2 Choix taille du format de donnees des caracteres
			registre : UCAxCTL0, USCI_Ax Control Register 0
			bit b4 (UC7BIT) Character length. Selects 7-bit or 8-bit character length.
			'0' 8-bit data
			'1' 7-bit data
		5.3. Choix bit de parite ou pas : Pas de bit de parite
			registre : UCAxCTL0, USCI_Ax Control Register 0
			Bit b7(UCPEN) Parity enable
			'0' Parity disabled.
			'1' Parity enabled. Parity bit is generated (UCAxTXD) and expected (UCAxRXD).
		5.4. Choix sens de tranfert des bit: LSB en premier
			registre : UCAxCTL0, USCI_Ax Control Register 0
			Bit(UCMSB) b5 MSB first select. Controls the direction of the receive and transmit shift register.
			'0' LSB first
			'1' MSB first


	6. Configurer la vitesse de transfert : Baudrate
		ValeurBaudrate=FrequenceHorlogeUART/Vitesse
		ex: Pour une frequence 1 MHz et une vitesse de 9600 bits/seconde
		ValeurBaudrate=1048576/9600 = 109.22 =109=0x6D
		UCA1BR0=0x6D et UCA1BR1=0x00
		Car 16 bits pour coder 0x682 et que les registres UCA0BR0 et UCA0BR1 sont des registres de 8bits

	7. Relacher le Reset (Deactiver) de la machine a etat du USCI_A1
		registre : UCAxCTL1, USCI_Ax Control Register 1
		bit b0 (UCSWRST)  Software reset enable
			'0' Disabled. USCI reset released for operation.
			'1' Enabled. USCI logic held in reset state.

	8. Configuration de la demande Interruption.
		Comme la plupart des peripherique, UART est Autonome
		Une fois configurer il travaille tout SEUL.
		Un caractere (code sur 8 bits) est recu/transmis bit par bit
		- les bits recus sont ranger dans le registre : UCA0RXBUF (USCI_Ax Receive Buffer Register), x=0
		  Le module compte les bits recus: Lorsqu'il fini la reception des 8bits
		  il met a '1' le bit b0 (UCA0RXIFG) du registre : IFG2, Interrupt Flag Register 2
			- On peut alors recuperer la valeur du caractere recu
				1. Soit en activant la demande Interruption lier a reception :
					- mettre a '1' le bit b0 (UCA0RXIE) du registre IE2, Interrupt Enable Register 2
					- ecrire la routine Interruption
				2. Soit en scrutant : Attendre que le bit b0 (UCA0RXIFG) de IFG2 passe a '1'.
		- les bits transmis sont ranger dans le registre UCAxTXBUF, USCI_Ax Transmit Buffer Register
			- On peut envoyer un caractere soit:
				1. Par interruption: Il faut activer la demande Interruption lier a Transmission
					- mettre a '1' le bit b1(UCA0TXIE) du registre IE2, Interrupt Enable Register 2
					- ecrire la routine Interruption
				2. Par scrutation : Attendre que le bit b1 (UCA0TXIFG) de IFG2 passe a '1'.

	-------------------------------------------------------------------------------------------------*/
	// 1. Configurer les pattes pour la liaison
	 // MSP430F5529 : // P4.5 = RXD, P4.4=TXD
	// mettre a '1' les bits b4 et b5 du registre P4SEL
	 // ecrire le code a la ligne ci-dessous

	//2. Choix horloge et configuration de la frequence pour le module USCIA0
		// Nous preons SMCLK configurer pour 1MHz Calibre: bits b7b6 du->"11"

		// mettre a '1' les bits b7 et b6 du registre UCA1CTL1
		// ecrire le code a la ligne ci-dessous


	// 3. Faire un reset (activer) de la state machine du USCI_A0
		// registre : UCAxCTL1, USCI_Ax Control Register 1
		// bit b0 (UCSWRST)  Software reset enable
		// 0 Disabled. USCI reset released for operation.
		// 1 Enabled. USCI logic held in reset state.

		// mettre a '1' le bits b0 du registre UCA1CTL1
		// ecrire le code a la ligne ci-dessous


	// 4. choix du mode asynchrone UART
	// 4.1 Choix asynchrone : bit b0 de UCAxCTL0 -> '0'
		// mettre a '0' le bits b0 du registre UCA1CTL0
		// ecrire le code a la ligne ci-dessous

		
	// 4.2 choix mode UART : bits b2b1 de UCA1CTL0 ->"00"

		// mettre a '0' les bits b2 et b1 du registre UCA1CTL0
		// ecrire le code a la ligne ci-dessous

	// 5.1 Choix nombre de bits STOP: Ici 1 BIT STOP: bit b3(UCSPB) de UCA1CTL0 ->'0'

		// mettre a '0' le bits b3 du registre UCA1CTL0
		// ecrire le code a la ligne ci-dessous
		

	//	5.2 Choix taille du format de donnees des caracteres: Caractere coder 8bits
		// bit b4 de UCA0CTL0->'0'

		// mettre a '0' le bits b4 du registre UCA1CTL0
		// ecrire le code a la ligne ci-dessous
		

	// 5.3. Choix bit de parite ou pas : Pas de bit de parite : bit b7(UCPEN) ->'0'

		// mettre a '0' le bits b7 du registre UCA1CTL0
		// ecrire le code a la ligne ci-dessous
		

	// 5.4. Choix sens de tranfert des bit: LSB en premier: Bitb5 (UCMSB)de UCA1CTL0 ->'0'
		
		// mettre a '0' le bits b5 du registre UCA1CTL0
		// ecrire le code a la ligne ci-dessous

	// 6. Configurer la vitesse de transfert : 9600
		// la formule de la valeur a ecrire pour choisir le baudrate est : Frequence/BaudRate
		// Frequence= 1048576
		// Baudrate = 9600 = 109.22 =109=0x6D
		// calculer la valeur a ecrire et convertir le resultat en hexadecimal puis ecrire
		// 1. octet de poids faible dans le registre UCA1BR0
		// 2. octet de poids fort dans le registre UCA1BR1

		// ecrire le code a la ligne ci-dessous

	// 7. Relacher le Reset (Deactiver) de la machine a etat du USCI_A1
		// bit b0 (UCSWRST) de UCA1CTL1 -> '0'
		// mettre a '0' le bits b0 du registre UCA1CTL1
		// ecrire le code a la ligne ci-dessous
		

    // 8. Configuration de la demande Interruption.
    // On ne souhaite pas interruption : Exercice 3

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


