#include "HelpDialog.h"

HelpDialog::HelpDialog() {
    mainDialogLayout = new QVBoxLayout(this);

    control = new QLabel(this);
    control->setText(tr("Mute/unmute: M\nPlay/pause: SPACE\nStop: ENTER\nSkip forward: RIGHT KEY\nSkip back: LEFT KEY\nOpen file: CTRL+O\nOpen files: CTRL+P\nOpen help: CTRL+H\nSave History: CTRL+S"));
    control->setStyleSheet("Font : 10pt");

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok);
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));

    mainDialogLayout->addWidget(control);
    mainDialogLayout->addWidget(buttonBox);
    mainDialogLayout->setAlignment(buttonBox, Qt::AlignHCenter);

    setLayout(mainDialogLayout);
    setWindowTitle(tr("Controls"));
}
