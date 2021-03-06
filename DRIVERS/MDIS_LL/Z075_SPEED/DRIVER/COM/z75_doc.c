/*********************  P r o g r a m  -  M o d u l e ***********************/
/*!
 *        \file  z75_doc.c
 *
 *      \author  rla
 *
 *      \brief   User documentation for Z75 module driver
 *
 *     Required: -
 *
 *     \switches -
 *
 *---------------------------------------------------------------------------
 * Copyright 2006-2019, MEN Mikro Elektronik GmbH
 ****************************************************************************/

 /*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/*! \mainpage
	This is the documentation of the MDIS low-level driver for the
	16Z075_SPEED FPGA module.

	The 16Z075_SPEED is a frequency counter implemented in an Chameleon FPGA.
	It supports the following features:

	- measuring frequency from 30 Hz .. est. 8 MHz depending on the
	  resolution setting
	- resolution (measurement time) configuration
	- Automated mode for frequency monitoring, reported by signals

	\n
	\section Variants Variants
	( no variants )
	\n \section FuncDesc Functional Description

	\n \subsection General General

	Before the the measurement is started by the corresponding M_SetStat
	Z075_START_MEAS, the Resolution and the FPGA system core clock has to
	be set. If not default values are taken from the descriptor file.

	In case of the driver is running in automated mode M_SetStat
	Z075_AUTO_MODE the Upper/Lower Limits have to be defined and the
	Signals for lower/upper range violation have to be installed before
	the automated mode should be enabled.

	\n \subsection reading Reading Frequency

	The application can read the measured frequency by the M_GetStat code
	Z075_FREQUENCY. The return value represent the frequency in Hz. If
	the Frequency can not be read the call will return an error. The
	frequency measurement is disabled by default and can be started by
	SetStat code Z075_START_MEAS and passing 1 as argument.

	\n \subsection automated Frequency Monitoring

	The application can enable the automated mode of the driver,
	which checks the measured frequency of lower and upper range limits.
	If the limits a exceeded the driver will inform the application via
	the installed signals.
	By default the automated mode is disabled. It can be enabled by the
	corresponding SetStat code passing the time in [ms] (how often the
	frequency is checked) as argument.

	\n \section signals Signals
	The driver can send signals to notify the application of changes on the
	signal lines . The signal must be activated via the Z075_SET_SIG_UPPER and
	Z075_SET_SIG_LOWER SetStat codes and can be cleared by SetStat codes
	Z075_CLR_SIG_UPPER/Z075_CLR_SIG_LOWER and passing 0 as argument.

	\n \section descriptor_entries Descriptor Entries

	The low-level driver initialization routine decodes the following entries
	("keys") in addition to the general descriptor keys:

	<table border="0">
	<tr><td><b>Descriptor entry</b></td>
		<td><b>Description</b></td>
		<td><b>Values</b></td>
	</tr>

	<tr><td>Z075_SYSCLK</td>
		<td>System clock of the 16Z075_SPEED FPGA core</td>
		<td>0..0xFFFFFFFF, default: 32000000</td>
	</tr>
	<tr><td>Z075_RESOLUTION</td>
		<td>Initial value for resolution setting in CTL_STS register</td>
		<td>0..0x7, default: 0</td>
	</tr>
	<tr><td>Z075_A_UPPER_LTD</td>
		<td>Upper Limit for automated mode</td>
		<td>0..0xFFFFFFFF, default: 0xFFFFFFFF</td>
	</tr>
	<tr><td>Z075_A_LOWER_LTD</td>
		<td>Lower Limit for automated mode</td>
		<td>0..0xFFFFFFFF, default: 0x0</td>
	</tr>
	</table>

	\n \section interrupts Interrupts
	The Z075_SPEED module doesn't generate any interrupts, so the driver
	doesn't support interrupt handling.

	\n \section api_functions Supported API Functions

	<table border="0">
	<tr>
		<td><b>API function</b></td>
		<td><b>Functionality</b></td>
		<td><b>Corresponding low level function</b></td></tr>

	<tr><td>M_open()</td><td>Open device</td><td>Z75_Init()</td></tr>

	<tr><td>M_close()     </td><td>Close device             </td>
	<td>Z75_Exit())</td></tr>
	<tr><td>M_read()      </td><td>not supported by driver  </td>
	<td>Z75_Read()</td></tr>
	<tr><td>M_write()     </td><td>not supported by driver  </td>
	<td>Z75_Write()</td></tr>
	<tr><td>M_setstat()   </td><td>Set device parameter  </td>
	<td>Z75_SetStat()</td></tr>
	<tr><td>M_getstat()   </td><td>Get device parameter  </td>
	<td>Z75_GetStat()</td></tr>
	<tr><td>M_getblock()  </td><td>not supported by driver  </td>
	<td>Z75_BlockRead()</td></tr>
	<tr><td>M_setblock()  </td><td>not supported by driver  </td>
	<td>Z75_BlockWrite()</td></tr>
	<tr><td>M_errstringTs() </td><td>Generate error message </td>
	<td>-</td></tr>
	</table>

	\n \section codes Z75 specific Getstat/Setstat codes
	see \ref getstat_setstat_codes "section about Getstat/Setstat codes"

	<table border="0">
	<tr><td><b>Status Code</b></td>
		<td><b>G/S</b></td>
		<td><b>Description</b></td>
		<td><b>Value Range</b></td>
	</tr>

	<tr><td>Z075_RESOLUTION</td>
		<td>S/G</td>
		<td>Access the CTL_STS register to set/get the resolution</td>
		<td>0..0x7, default: 0</td>
	</tr>

	<tr><td>Z075_FREQUENCY</td>
		<td>G</td>
		<td>Retrieve the measured frequency or evtl. errors</td>
		<td>0..0xFFFFFFFF</td>
	</tr>

	<tr><td>Z075_SET_SIG_UPPER</td>
		<td>S</td>
		<td>Install the signal for the automated mode, upper limit violation</td>
		<td>0..0xFFFFFFFF</td>
	</tr>

	<tr><td>Z075_SET_SIG_LOWER</td>
		<td>S</td>
		<td>Install the signal for the automated mode, lower limit violation</td>
		<td>0..0xFFFFFFFF</td>
	</tr>

	<tr><td>Z075_CLR_SIG_UPPER</td>
		<td>S</td>
		<td>Uninstall the signal for the automated mode, upper limit violation</td>
		<td>0..0xFFFFFFFF</td>
	</tr>

	<tr><td>Z075_CLR_SIG_LOWER</td>
		<td>S</td>
		<td>Uninstall the signal for the automated mode, lower limit violation</td>
		<td>0..0xFFFFFFFF</td>
	</tr>

	<tr><td>Z075_A_UPPER_LTD</td>
		<td>S/G</td>
		<td>Upper Limit for automated mode</td>
		<td>0..0xFFFFFFFF</td>
	</tr>

	<tr><td>Z075_A_LOWER_LTD</td>
		<td>S/G</td>
		<td>Lower Limit for automated mode</td>
		<td>0..0xFFFFFFFF</td>
	</tr>

	<tr><td>Z075_START_MEAS</td>
		<td>S/G</td>
		<td>Start/Stop measurement</td>
		<td>0..0x1</td>
	</tr>

	<tr><td>Z075_AUTO_MODE</td>
		<td>S/G</td>
		<td>En/Disable automate mode</td>
		<td>0..0xFFFFFFFF</td>
	</tr>

	</table>


	\n \section Documents Overview of all Documents

	\subsection z75_simp  Simple example for using the driver
	z75_simp.c (see example section)
*/

/** \example z75_simp.c
Simple example for driver usage

The example can be configured to measure/display the frequency continuously or
to monitor the frequency and report a frequency violation by evaluating a
installed signal.
*/

/** \page dummy
  \menimages
*/

