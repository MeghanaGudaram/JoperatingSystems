#ifndef JOS_KERN_E1000_H
#define JOS_KERN_E1000_H

#include <kern/pci.h>
#include <kern/pmap.h>
#include <inc/string.h>

#define	PCI_E1000_VENDORID		0x8086
#define	PCI_E1000_DEVICEID		0x100E
#define E1000_TDBAL    			0x03800/4  /* TX Descriptor Base Address Low - RW */
#define E1000_TDBAH    			0x03804/4  /* TX Descriptor Base Address High - RW */
#define E1000_TDLEN    			0x03808/4  /* TX Descriptor Length - RW */
#define E1000_TDH      			0x03810/4  /* TX Descriptor Head - RW */
#define E1000_TDT      			0x03818/4  /* TX Descripotr Tail - RW */
#define E1000_TIPG     			0x00410/4  /* TX Inter-packet gap -RW */
#define E1000_CTRL_ILOS     	0x00000080/4  /* Invert Loss-Of Signal */
#define E1000_TCTL     			0x00400/4  /* TX Control - RW */

#define E1000_TCTL_EN     		0x00000002    /* enable tx */
#define E1000_TCTL_PSP    		0x00000008    /* pad short packets */
#define E1000_TCTL_CT     		0x00000ff0    /* collision threshold */
#define E1000_TCTL_COLD   		0x003ff000    /* collision distance */

#define E1000_TX_MAXDESC        64
#define E1000_TXPKT_MAX         1518

#define E1000_RX_MAXDESC        128
#define E1000_RXPKT_MAX         2048

// Receivers definitions

#define E1000_RA       0x05400/4  /* Receive Address - RW Array */
#define E1000_IMS      0x000D0/4  /* Interrupt Mask Set - RW */
#define E1000_RDTR     0x02820/4  /* RX Delay Timer - RW */
#define E1000_RDBAL    0x02800/4  /* RX Descriptor Base Address Low - RW */
#define E1000_RDBAH    0x02804/4  /* RX Descriptor Base Address High - RW */
#define E1000_RDLEN    0x02808/4  /* RX Descriptor Length - RW */
#define E1000_RDH      0x02810/4  /* RX Descriptor Head - RW */
#define E1000_RDT      0x02818/4  /* RX Descriptor Tail - RW */
#define E1000_RCTL     0x00100/4  /* RX Control - RW */

#define E1000_ICR_LSC           0x00000004 /* Link Status Change */
#define E1000_ICR_RXSEQ         0x00000008 /* rx sequence error */
#define E1000_ICR_RXDMT0        0x00000010 /* rx desc min. threshold (0) */
#define E1000_ICR_RXO           0x00000040 /* rx overrun */
#define E1000_ICR_RXT0          0x00000080 /* rx timer intr (ring 0) */
#define E1000_IMS_LSC       E1000_ICR_LSC       /* Link Status Change */
#define E1000_IMS_RXSEQ     E1000_ICR_RXSEQ     /* rx sequence error */
#define E1000_IMS_RXDMT0    E1000_ICR_RXDMT0    /* rx desc min. threshold */
#define E1000_IMS_RXO       E1000_ICR_RXO       /* rx overrun */
#define E1000_IMS_RXT0      E1000_ICR_RXT0      /* rx timer intr */
#define E1000_RCTL_EN             0x00000002    /* enable */
#define E1000_RCTL_LPE            0x00000020    /* long packet enable */
#define E1000_RCTL_LBM_NO         0x00000000    /* no loopback mode */
#define E1000_RCTL_BAM            0x00008000    /* broadcast enable */
#define E1000_RCTL_SZ_2048        0x00000000    /* rx buffer size 2048 */
#define E1000_RCTL_SECRC          0x04000000    /* Strip Ethernet CRC */
#define E1000_RAH_AV  0x80000000        /* Receive descriptor valid */

/* Packet Definition */
struct packets_tx
{
	char buffer[E1000_TXPKT_MAX];
};

/* Packet Definition */
struct packets_rx
{
	char buffer[E1000_RXPKT_MAX];
};

/* Transmit Descriptor */
struct e1000_tx_desc {
    uint64_t buffer_addr;       /* Address of the descriptor's data buffer */
    union {
        //uint32_t data;
        struct {
            uint16_t length;    /* Data buffer length */
            uint8_t cso;        /* Checksum offset */
            uint8_t cmd;        /* Descriptor control */
        } flags;
    } lower;
    union {
        //uint32_t data;
        struct {
            uint8_t status;     /* Descriptor status */
            uint8_t css;        /* Checksum start */
            uint16_t special;
        } fields;
    } upper;
};

/* Receive Descriptor */
struct e1000_rx_desc {
    uint64_t buffer_addr; /* Address of the descriptor's data buffer */
    uint16_t length;     /* Length of data DMAed into data buffer */
    uint16_t csum;       /* Packet checksum */
    uint8_t status;      /* Descriptor status */
    uint8_t errors;      /* Descriptor Errors */
    uint16_t special;
};

int pci_attach_enable (struct pci_func *pcif);
int transmit_enable();

volatile uint32_t *e1000Base;

#endif	// JOS_KERN_E1000_H
