# StudentNodeElements

StudentNodeElements (SNE) is a library build upon the [ProcessorNode](https://github.com/PipesAndFiltersProject/ProcessorNode) library.

The purpose of SNE is to provide an application specific layer on top of ProcessorNode, for applications handling student data related to passing courses.

This library then makes it easier to build apps on a ProcessorNode type of architecture for the domain of handling student performance data:

* Basic information about students taking a course,
* How many points a student got from course exercises,
* How many points a student got from course exam, and
* How many points students got from the course project.

Additionally, the SNE provides different ways **grading**, calculating the student's grade based on the points above. **Reporting** enables saving the performance data of the students into a file. This file can then be sent to the registrars to actually enter the grades to the appropriate systems.

It should also be possible to design and implement a feature that actually exports the data to the registrar system automatically, if such an API would be available. 

Currently there is one app using this library, the StudentPassing. 

For more information, see the [ProcessorNode](https://github.com/PipesAndFiltersProject/ProcessorNode) library documentation as well as the [StudentPassing](https://github.com/PipesAndFiltersProject/StudentPassing) app.

## Who do I talk to?

Repo is owned and maintained by Antti Juustila (antti.juustila at oulu.fi)

## License

(c) Antti Juustila 2014-2020. This software is licensed in [GPL version 2 or later](https://opensource.org/licenses/gpl-2.0.php).


