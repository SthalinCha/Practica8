#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->listWidget, &QListWidget::itemClicked, this, &MainWindow::on_listWidget_itemClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QString directory = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "C:/Users/USER/Desktop/ProyectosQt", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if (!directory.isEmpty()) {
        ui->label->setText(directory);

        QDir dir(directory);
        QStringList entries = dir.entryList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot); // Obtener archivos de la carpeta

        ui->listWidget->clear(); // Limpia
        for (const QString& entry : entries) {
            ui->listWidget->addItem(entry);
        }
    }
}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    QString fullPath = QDir(ui->label->text()).filePath(item->text()); // Obtiene dirección del archivo/directorio seleccionado
    QFileInfo fileInfo(fullPath);

    ui->Propiedades->clear(); // Limpia las propiedades
    ui->Propiedades->addItem("Nombre del Archivo: " + fileInfo.fileName());
    ui->Propiedades->addItem("Ubicación: " + fileInfo.absoluteFilePath());
    ui->Propiedades->addItem("Extensión: " + fileInfo.suffix());
    ui->Propiedades->addItem("Tamaño: " + QString::number(fileInfo.size()) + " bytes");
    ui->Propiedades->addItem(fileInfo.isFile() ? "Es un archivo" : "No es un archivo");
    ui->Propiedades->addItem("Fecha de última modificación: " + fileInfo.lastModified().toString());

    if (fileInfo.isDir()) {
        QDir dir(fullPath);
        int fileCount = dir.count() - 2; // Restar 2 para excluir las referencias "." y ".."
        ui->Propiedades->addItem("Cantidad de archivos en la carpeta: " + QString::number(fileCount));

        QDateTime creationTime = fileInfo.birthTime();
        ui->Propiedades->addItem("Fecha de creación: " + creationTime.toString());
    }
}
//a
