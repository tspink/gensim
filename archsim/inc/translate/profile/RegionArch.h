/* This file is Copyright University of Edinburgh 2018. For license details, see LICENSE. */

/*
 * RegionArch.h
 *
 *  Created on: 5 Aug 2014
 *      Author: harry
 */

#ifndef REGIONARCH_H_
#define REGIONARCH_H_

#include "define.h"

namespace archsim
{
	namespace translate
	{
		namespace profile
		{

			class RegionArch
			{
			public:
				RegionArch() = delete;

				static const uint32_t PageBits = 12;
				static const uint32_t PageSize = 1 << PageBits;
				static const uint32_t PageMask = PageSize - 1;
				static const uint32_t PageCount = 1 << ((32 - PageBits));

				static constexpr addr_t PageOffsetOf(addr_t addr) __attribute__((pure))
				{
					return addr & RegionArch::PageMask;
				}

				static constexpr addr_t PageBaseOf(addr_t addr) __attribute__((pure))
				{
					return addr & ~RegionArch::PageMask;
				}

				static constexpr addr_t PageIndexOf(addr_t addr) __attribute__((pure))
				{
					return addr >> RegionArch::PageBits;
				}

				static constexpr bool IsPageAligned(addr_t addr) __attribute__((pure))
				{
					return PageOffsetOf(addr) == 0;
				}
			};

		}
	}
}


#endif /* REGIONARCH_H_ */
