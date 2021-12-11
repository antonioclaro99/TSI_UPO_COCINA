# -*- coding: utf-8 -*-

from odoo import models, fields, api
import re


class Personas(models.Model):
     
     _name = 'cocina.personas'
     _description = 'cocina personas'
     _rec_name='dni'

     nombre = fields.Char(string="nombre", required=True, help="nombre de la persona")
     apellidos = fields.Char(string="apellidos", required=True, help="apellidos de la persona")
     dni = fields.Char('DNI', size=9, required=True)
     email  = fields.Char('Email', required=True)
     telefono  = fields.Integer('Telefono', required=True)

     _sql_constraints = [('personas_dni_unique','UNIQUE (dni)','El dni debe ser único')]


     @api.constrains('dni')
     def comprobarDni(self):
          patron="^[0-9]{8,8}[A-Za-z]$"
          regex= re.compile(patron)
          if(not regex.match(self.dni)):
               raise models.ValidationError("El dni debe ser 8 numeros y una letra")

     @api.constrains('nombre')
     def comprobarNombre(self):
          patron="^[A-Za-z\s]*$"
          regex= re.compile(patron)
          if(not regex.match(self.nombre)):
               raise models.ValidationError("El nombre solo puede contener letras y espacios")


     @api.constrains('apellidos')
     def comprobarA(self):
          patron="^[A-Za-z\s]*$"
          regex= re.compile(patron)
          if(not regex.match(self.apellidos)):
               raise models.ValidationError("Los apellidos solo puede contener letras y espacios")