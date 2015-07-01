/*
 * AgeBlock.cpp
 *
 * Copyright (C) 2015 IBR, TU Braunschweig
 *
 * Written-by: Bjoern Gernert <gernert@ibr.cs.tu-bs.de>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include "ibrdtn/data/DBlock.h"

namespace dtn
{
	namespace data
	{
		const dtn::data::block_t DBlock::BLOCK_TYPE = 233;

		dtn::data::Block* DBlock::Factory::create()
		{
			return new DBlock();
		}

		DBlock::DBlock()
		 : dtn::data::Block(DBlock::BLOCK_TYPE)
		{
		}

		DBlock::~DBlock()
		{
		}

		void DBlock::setVar1(dtn::data::Integer value)
		{
			_var1 = value;
		}

		void DBlock::setVar2(dtn::data::BundleString value)
		{
			_var2 = value;
		}

		dtn::data::Length DBlock::getLength() const
		{
			return _var1.getLength() + _var2.getLength();
		}

		std::ostream& DBlock::serialize(std::ostream &stream, dtn::data::Length &length) const
		{
			stream << _var1 << _var2;
			length += getLength();
			return stream;
		}

		std::istream& DBlock::deserialize(std::istream &stream, const dtn::data::Length&)
		{
			stream >> _var1 >> _var2;
			return stream;
		}
	}
}
