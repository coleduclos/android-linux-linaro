/*
 * Remote processor resource manager common resources
 *
 * Copyright(c) 2012 Texas Instruments. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in
 *   the documentation and/or other materials provided with the
 *   distribution.
 * * Neither the name Texas Instruments nor the names of its
 *   contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _LINUX_RPMSG_RESMGR_COMMON_H
#define _LINUX_RPMSG_RESMGR_COMMON_H

/**
 * struct rprm_regulator - resource manager parameters for regulator
 * @name:	name of the regulator
 * @min_uv	minimum voltage in micro volts
 * @max_uv	maximum voltage in micro volts
 */
struct rprm_regulator {
	char name[16];
	u32 min_uv;
	u32 max_uv;
} __packed;

/**
 * struct rprm_gpio - resource manager parameters for GPIO
 * @id:		id of the requested GPIO
 */
struct rprm_gpio {
	u32 id;
};

/**
 * struct rprm_i2c - resource manager parameters for i2c
 * @id:         id of the requested i2c
 */
struct rprm_i2c {
	u32 id;
};

/**
 * struct rprm_rproc - resource manager parameters for remote proc
 * @id:         name of the remote proc requested
 */
struct rprm_rproc {
	char name[16];
};
#endif /* _LINUX_RPMSG_RESMGR_COMMON_H */
