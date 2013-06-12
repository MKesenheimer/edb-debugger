/*
Copyright (C) 2006 - 2013 Evan Teran
                          eteran@alum.rit.edu

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "Assembler.h"
#include "DialogAssembler.h"
#include "Debugger.h"
#include "MemoryRegions.h"
#include "Debugger.h"
#include <QMenu>
#include <QList>
#include <QAction>

//------------------------------------------------------------------------------
// Name: Assembler
// Desc:
//------------------------------------------------------------------------------
Assembler::Assembler() : menu_(0), dialog_(0) {
}

//------------------------------------------------------------------------------
// Name: ~Assembler
// Desc:
//------------------------------------------------------------------------------
Assembler::~Assembler() {
	delete dialog_;
}

//------------------------------------------------------------------------------
// Name: cpu_context_menu
// Desc:
//------------------------------------------------------------------------------
QList<QAction *> Assembler::cpu_context_menu() {

	QList<QAction *> ret;

	QAction *const action_assemble = new QAction(tr("Assemble"), this);

	connect(action_assemble, SIGNAL(triggered()), this, SLOT(show_menu()));
	ret << action_assemble;

	return ret;
}

//------------------------------------------------------------------------------
// Name: menu
// Desc:
//------------------------------------------------------------------------------
QMenu *Assembler::menu(QWidget *parent) {

	if(menu_ == 0) {
	}

	return menu_;
}

//------------------------------------------------------------------------------
// Name: show_menu
// Desc:
//------------------------------------------------------------------------------
void Assembler::show_menu() {

	if(dialog_ == 0) {
		dialog_ = new DialogAssembler(edb::v1::debugger_ui);
	}
	
	const edb::address_t address = edb::v1::cpu_selected_address();
	if(IRegion::pointer region = edb::v1::memory_regions().find_region(address)) {
		if(DialogAssembler *const d = qobject_cast<DialogAssembler *>(dialog_)) {
			d->set_address(address);
		}
		dialog_->show();
	}
}

Q_EXPORT_PLUGIN2(Assembler, Assembler)
