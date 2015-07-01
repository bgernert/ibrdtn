/*
 * DBlock.h
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

#include <ibrdtn/data/Block.h>
#include <ibrdtn/data/Number.h>
#include <ibrdtn/data/BundleString.h>
#include <ibrdtn/data/ExtensionBlock.h>

#ifndef DLOCK_H_
#define DLOCK_H_

namespace dtn
{
	namespace data
	{
		class DBlock : public dtn::data::Block
		{
		public:
			class Factory : public dtn::data::ExtensionBlock::Factory
			{
			public:
				Factory() : dtn::data::ExtensionBlock::Factory(DBlock::BLOCK_TYPE) {};
				virtual ~Factory() {};
				virtual dtn::data::Block* create();
			};

			static const dtn::data::block_t BLOCK_TYPE;

			DBlock();
			virtual ~DBlock();

			virtual dtn::data::Length getLength() const;
			virtual std::ostream &serialize(std::ostream &stream, dtn::data::Length &length) const;
			virtual std::istream &deserialize(std::istream &stream, const dtn::data::Length &length);

			void setVar1(dtn::data::Integer value);
			void setVar2(dtn::data::BundleString value);

		private:
			dtn::data::Integer _var1;
			dtn::data::BundleString _var2;
		};

		/**
		 * This creates a static block factory
		 */
		static DBlock::Factory __DBlockFactory__;
	}
}

#endif /* DBLOCK_H_ */
