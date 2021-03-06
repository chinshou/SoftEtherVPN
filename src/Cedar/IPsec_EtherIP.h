// SoftEther VPN Source Code
// Cedar Communication Module
// 
// SoftEther VPN Server, Client and Bridge are free software under GPLv2.
// 
// Copyright (c) 2012-2014 Daiyuu Nobori.
// Copyright (c) 2012-2014 SoftEther VPN Project, University of Tsukuba, Japan.
// Copyright (c) 2012-2014 SoftEther Corporation.
// 
// All Rights Reserved.
// 
// http://www.softether.org/
// 
// Author: Daiyuu Nobori
// Comments: Tetsuo Sugiyama, Ph.D.
// 
// 
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// version 2 as published by the Free Software Foundation.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License version 2
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
// CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
// SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
// 
// THE LICENSE AGREEMENT IS ATTACHED ON THE SOURCE-CODE PACKAGE
// AS "LICENSE.TXT" FILE. READ THE TEXT FILE IN ADVANCE TO USE THE SOFTWARE.
// 
// 
// THIS SOFTWARE IS DEVELOPED IN JAPAN, AND DISTRIBUTED FROM JAPAN,
// UNDER JAPANESE LAWS. YOU MUST AGREE IN ADVANCE TO USE, COPY, MODIFY,
// MERGE, PUBLISH, DISTRIBUTE, SUBLICENSE, AND/OR SELL COPIES OF THIS
// SOFTWARE, THAT ANY JURIDICAL DISPUTES WHICH ARE CONCERNED TO THIS
// SOFTWARE OR ITS CONTENTS, AGAINST US (SOFTETHER PROJECT, SOFTETHER
// CORPORATION, DAIYUU NOBORI OR OTHER SUPPLIERS), OR ANY JURIDICAL
// DISPUTES AGAINST US WHICH ARE CAUSED BY ANY KIND OF USING, COPYING,
// MODIFYING, MERGING, PUBLISHING, DISTRIBUTING, SUBLICENSING, AND/OR
// SELLING COPIES OF THIS SOFTWARE SHALL BE REGARDED AS BE CONSTRUED AND
// CONTROLLED BY JAPANESE LAWS, AND YOU MUST FURTHER CONSENT TO
// EXCLUSIVE JURISDICTION AND VENUE IN THE COURTS SITTING IN TOKYO,
// JAPAN. YOU MUST WAIVE ALL DEFENSES OF LACK OF PERSONAL JURISDICTION
// AND FORUM NON CONVENIENS. PROCESS MAY BE SERVED ON EITHER PARTY IN
// THE MANNER AUTHORIZED BY APPLICABLE LAW OR COURT RULE.
// 
// USE ONLY IN JAPAN. DO NOT USE IT IN OTHER COUNTRIES. IMPORTING THIS
// SOFTWARE INTO OTHER COUNTRIES IS AT YOUR OWN RISK. SOME COUNTRIES
// PROHIBIT ENCRYPTED COMMUNICATIONS. USING THIS SOFTWARE IN OTHER
// COUNTRIES MIGHT BE RESTRICTED.
// 
// 
// DEAR SECURITY EXPERTS
// ---------------------
// 
// If you find a bug or a security vulnerability please kindly inform us
// about the problem immediately so that we can fix the security problem
// to protect a lot of users around the world as soon as possible.
// 
// Our e-mail address for security reports is:
// softether-vpn-security [at] softether.org
// 
// Please note that the above e-mail address is not a technical support
// inquiry address. If you need technical assistance, please visit
// http://www.softether.org/ and ask your question on the users forum.
// 
// Thank you for your cooperation.


// IPsec_EtherIP.h
// Header of IPsec_EtherIP.c

#ifndef	IPSEC_ETHERIP_H
#define	IPSEC_ETHERIP_H

//// Macro


//// Constants
#define	ETHERIP_VPN_CONNECT_RETRY_INTERVAL		(15 * 1000)	// VPN connection retry interval
#define	ETHERIP_CLIENT_NAME						"EtherIP Client"
#define	ETHERIP_POSTFIX							"ETHERIP"
#define	ETHERIP_L2TPV3_CLIENT_NAME				"L2TPv3 Client"
#define	ETHERIP_L2TPV3_CLIENT_NAME_EX			"L2TPv3 Client - %s"
#define	ETHERIP_L2TPV3_POSTFIX					"L2TPV3"

//// Type

// EtherIP server
struct ETHERIP_SERVER
{
	REF *Ref;
	CEDAR *Cedar;
	IPSEC_SERVER *IPsec;
	LOCK *Lock;
	UINT Id;
	IKE_SERVER *Ike;
	UINT64 Now;									// Current time
	INTERRUPT_MANAGER *Interrupts;				// Interrupt manager
	SOCK_EVENT *SockEvent;						// SockEvent
	char CryptName[MAX_SIZE];					// Cipher algorithm name
	LIST *SendPacketList;						// Transmission packet list
	UINT64 LastConnectFailedTick;				// Time that it fails to connect at the last
	IPC *Ipc;									// IPC
	THREAD *IpcConnectThread;					// IPC connection thread
	IPSEC_SERVICES CurrentIPSecServiceSetting;	// Copy of the current IPsec service settings
	IP ClientIP, ServerIP;
	UINT ClientPort, ServerPort;
	bool IsTunnelMode;							// Whether the IPsec is in the tunnel mode
	UINT CryptBlockSize;						// Encryption block size of IPsec
	char ClientId[MAX_SIZE];					// Client ID has been presented by the IPsec connection
	UINT LastEtherIPSettingVerNo;				// Version number of EtherIP settings last checked
	ETHERIP_ID CurrentEtherIPIdSetting;			// Current EtherIP ID settings
	bool L2TPv3;								// L2TPv3 mode
	char VendorName[MAX_SIZE];					// Vendor name
};


//// Function prototype
ETHERIP_SERVER *NewEtherIPServer(CEDAR *cedar, IPSEC_SERVER *ipsec, IKE_SERVER *ike,
								 IP *client_ip, UINT client_port, IP *server_ip, UINT server_port, char *crypt_name,
								 bool is_tunnel_mode, UINT crypt_block_size,
								 char *client_id, UINT id);
void ReleaseEtherIPServer(ETHERIP_SERVER *s);
void CleanupEtherIPServer(ETHERIP_SERVER *s);
void SetEtherIPServerSockEvent(ETHERIP_SERVER *s, SOCK_EVENT *e);
void EtherIPProcInterrupts(ETHERIP_SERVER *s);
void EtherIPProcRecvPackets(ETHERIP_SERVER *s, BLOCK *b);
void EtherIPIpcConnectThread(THREAD *t, void *p);
UINT CalcEtherIPTcpMss(ETHERIP_SERVER *s);


#endif	// IPSEC_ETHERIP_H



// Developed by SoftEther VPN Project at University of Tsukuba in Japan.
// Department of Computer Science has dozens of overly-enthusiastic geeks.
// Join us: http://www.tsukuba.ac.jp/english/admission/
