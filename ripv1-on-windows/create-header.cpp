#include<stdlib.h>
#include<stdio.h>

void reset_header(unsigned*, int);

//RIP�p�̃w�b�_�[�𐶐����z��Ƃ��ĕԂ��֐�
/*
*0                           16                       31
*+-------------+-------------+------------------------+
*|command(8bit)|version(8bit)|0(16bit)                |
*+---------------------------+------------------------+
*|afi(16bit)                 |0(16bit)                |
*+----------------------------------------------------+
*                                                     63
*/
void generate_rip_header(unsigned *header,int header_length,int command, int version, int afi) {
	//�w�b�_�[��0�Ń��Z�b�g
	reset_header(header, header_length);

	//header_length==2�̏ꍇ�̂�RIP�w�b�_�[���쐬���ĕԂ�
	if (header_length == 2) {
		unsigned long int head1 = 0x00000000;
		unsigned long int head2 = 0x00000000;

		head1 = head1 | command;
		head1 = head1 << 8;
		head1 = head1 | version;
		head1 = head1 << 16;

		head2 = head2 | afi;
		head2 = head2 << 16;

		*header = head1;
		*(header + 1) = head2;
	}
}

//RIP�p��IPAddress���܂ރw�b�_�[�𐶐�
/*
0
+----------------------------------------------------+
|IP Address(32bit)                                   |
+----------------------------------------------------+
|0(32bit)                                            |
+----------------------------------------------------+
|0(32bit)                                            |
+----------------------------------------------------+
|metric(32bit)                                       |
+----------------------------------------------------+
*/
void generate_rip_header_ip(unsigned* header, int header_length, unsigned __int32 ip_addr, unsigned __int32 metric) {
	//�w�b�_�[�����Z�b�g
	 reset_header(header, header_length);

	//header_length==4�̏ꍇ�̂�IP�w�b�_�[���쐬
	if (header_length == 4) {
		*header = ip_addr;
		*(header + 3) = metric;
	}
}

//�w�b�_�[����������֐�
void cupling_header(unsigned* header_a, int header_a_length, unsigned* header_b, int header_b_length, unsigned *out) {
	reset_header(out, header_a_length + header_b_length);

	for (int i = 0; i < header_a_length;i++) {
		*(out + i) = *(header_a + i);
		printf("add index %d:%#08x\n", i, *(out + i));
	}

	for (int i = 0; i < header_b_length; i++) {
		*(out + i+header_a_length) = *(header_b + i);
		printf("add index %d:%#08x\n", i+header_a_length, *(out + i));
	}

}

//�w�b�_�[��0�Ƀ��Z�b�g����֐�
void reset_header(unsigned* header, int length) {
	for (int i = 0; i < length; i++) {
		*(header + i) = 0x00000000;
	}
}