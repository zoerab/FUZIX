/* 
 * Dummy fd driver code
 *
 */

#include <kernel.h>
#include <kdata.h>
#include <printf.h>
#include <devfd.h>

__sfr __at 0x80 control;
__sfr __at 0x81 track;
__sfr __at 0x82 sector;
__sfr __at 0x83 data;

int fd_open(uint8_t minor, uint16_t flag)
{
    flag;
    if(minor != 0) {
        udata.u_error = ENODEV;
        return -1;
    }
    return 0;
}


static int fd_transfer(bool is_read, uint8_t rawflag)
{
	blkno_t block;
	uint8_t* dptr;
	int count;
	uint8_t s;

	uint8_t sec, trk, side;

	if (rawflag != 0)
		return 0;

	dptr = (uint8_t*)udata.u_buf->bf_data;
	block = udata.u_buf->bf_blk;

	block <<= 1;

	sec = block & 0xF;
	trk = (block >> 5);
	side = ((block >> 4) & 0x1);

	kprintf("side %d, trk %d\r\n", side, trk);

	sector = sec;
	track = trk;
	control = side << 4;

	for (s = 0; s < 2; s++)
	{
		kprintf("sec %d\r\n", sec);
		count = 256;
		while (--count >= 0)
			if (is_read)
				*(dptr++) = data;
			else
				data = *(dptr++);
		sec++;
		sector = sec;
	}
	return 1;
}

int fd_read(uint8_t minor, uint8_t rawflag, uint8_t flag)
{
    flag;minor;
    kprintf("Reading block %d\r\n",udata.u_buf->bf_blk );
    return fd_transfer(true, rawflag);
}

int fd_write(uint8_t minor, uint8_t rawflag, uint8_t flag)
{
    flag;minor;
    return fd_transfer(false, rawflag);
}

